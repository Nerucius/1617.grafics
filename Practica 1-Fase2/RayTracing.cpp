
/* 
 * File:   RayTracing.cpp
 * Author: anna
 *
 * Created on 2 de enero de 2017, 19:43
 */

#include <cstdlib>
#include "RayTracing.h"
#include "stdio.h"

using namespace std;

// Metode per netejar la memòria
void cleanup() {
    delete scene;
}

/* FrameBuffer memory for multithreaded code */
vec3** FRAME_BUFFER;
vector<vec2> AA_SAMPLES;
// Samples must be 0 / 4 / 8
// SSAAx0 SSAAx4 or SSAAx8 Anti-Aliasing
int NUM_SAMPLES = 8;
int REC_DEPTH = 8;

// Metode Render

// Aquest metode, depenent si té activat o no GLUT, pinta pixels pinta pixels en la finestra GL usant GL_POINT o
// crea un fitxer anomenat resultat.ppm. En el cas de GLUT  es crida cada vegada que cal refrescar la pantalla. En el cas de no usar GLUT
// només s'executa un cop.

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel
// 3) Actualitza la finestra GL fent flush de les intruccions GL, si es el cas. Sino, posa el color en un fitxer

//Precondicio:
// La Scene i la Camera han d'estar creades i inicialitzades

void Render()
{


#ifndef GLUT
    // Les seguents linieas permeten escriure en un fitxer, el output i
    // prescindir de glut para visualitzar la imatge
      std::ofstream out("resultat.ppm");
      std::streambuf *coutbuf = std::cout.rdbuf(); //salvar el buf antic
      std::cout.rdbuf(out.rdbuf()); //redireccio de  std::cout al out.txt!
      std::cout << "P3\n" << scene->cam->viewportX << " " << scene->cam->viewportY << "\n255\n";

#else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Netejar la finestra OpenGL
    glBegin(GL_POINTS);	//S'activa el mode GL_POINTS. En aquest mode
                        // cada vertex especificat és un punt.
                        //Reference https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3 si us interessa.
#endif

    // algorisme de RayTracing
    // Recorregut de cada pixel de la imatge final
    for (int y = scene->cam->viewportY-1; y >= 0; y--) {
         for (int x = 0; x < scene->cam->viewportX; x++) {

            vec3 col(0, 0, 0);

            for(int i = 0; i < NUM_SAMPLES; i++){
                float u = float(x) / float(scene->cam->viewportX);
                float v = float(y) / float(scene->cam->viewportY);
                u += AA_SAMPLES[i].x;
                v += AA_SAMPLES[i].y;
                Ray r = scene->cam->getRay(u, v);
                col += scene->ComputeColor(r, REC_DEPTH) / ((float)NUM_SAMPLES+1);
            }

#ifdef GLUT
            float pixelX =  2*((x+0.5f)/scene->cam->viewportX)-1;
            float pixelY = 2*((y+0.5f)/scene->cam->viewportY)-1;

             glColor3f(col[0], col[1], col[2]);
             glVertex3f(pixelX, pixelY, 0.0f);
#else
             // Aquestes tres lineas permitirien fer una sortida en un ppm per ser visualitzat per un gimp o similar
             int ir = int(255.99*col[0]);
             int ig = int(255.99*col[1]);
             int ib = int(255.99*col[2]);
             std::cout << ir << " " << ig << " " << ib << "\n";
#endif
        }
     }
#ifdef GLUT
    glEnd();
    glFlush();
#else

#endif

}

/**
 * Rendering function, redesigned for Parallel Computing of scene
 * Rays. Considerably faster than the alternative single-threaded
 * Render().
 *
 * *NOTE*: Do not call ANY OpenGL methods inside the parallel block.
 * OpenGL context is exclusive to the master thread (The thread that
 * created it in the first place)
 *
 */
void Render_omp(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Netejar la finestra OpenGL
    glBegin(GL_POINTS);

    //S'activa el mode GL_POINTS. En aquest mode
    // cada vertex especificat és un punt.
    //Reference https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3 si us interessa.
    // algorisme de RayTracing

    // Recorregut de cada pixel de la imatge final
#pragma omp parallel for schedule(guided) collapse(2)
    for (int y = scene->cam->viewportY-1; y >= 0; y--) {
         for (int x = 0; x < scene->cam->viewportX; x++) {
            int FB_INDEX = y*scene->cam->viewportX + x;

            // Get framebuffer pixel
            vec3* col = FRAME_BUFFER[FB_INDEX];
            col->r = col->g = col->b = 0;

            // Sample scene points
            for(int i = 0; i < NUM_SAMPLES+1; i++){
                float u = float(x) / float(scene->cam->viewportX);
                float v = float(y) / float(scene->cam->viewportY);
                u += AA_SAMPLES[i].x;
                v += AA_SAMPLES[i].y;
                Ray r = scene->cam->getRay(u, v);
                *col += scene->ComputeColor(r, REC_DEPTH) / ((float)NUM_SAMPLES+1);
            }
         }
      }

    // OpenGL calls must run in a single thread
    for (int y = scene->cam->viewportY-1; y >= 0; y--) {
        for (int x = 0; x < scene->cam->viewportX; x++) {
            int FB_INDEX = y*scene->cam->viewportX + x;
            vec3* col = FRAME_BUFFER[FB_INDEX];
            float pixelX = 2*((x+0.5f)/scene->cam->viewportX)-1;
            float pixelY = 2*((y+0.5f)/scene->cam->viewportY)-1;

            // PostProcessing here
            // Gamma Correction
            col->r = sqrt(col->r);
            col->g = sqrt(col->g);
            col->b = sqrt(col->b);

            glColor3f(col->r, col->g, col->b);
            glVertex3f(pixelX, pixelY, 0.0f);
        }
    }

    glEnd();
    glFlush();
    // uncoment to enable display re-draw
    //glutPostRedisplay();
}

void initSuperSamplingAA(){
    // Anti Aliasing Init

    // half-pixel (adjusted for best image quality)
    float hp = .65 / scene->cam->viewportX;

    // Precompute Sine and Cosie of 26.6º. Chosen due to best
    // visual clarity for SSAA based on a rotated grid pattern
    float lcos = cos(26.6 * (M_PI/180.0));
    float lsin = sin(26.6 * (M_PI/180.0));
    float rcos = cos((45+26.6) * (M_PI/180.0));
    float rsin = sin((45+26.6) * (M_PI/180.0));

    // Create sampling points, as offset from the center of the pixel
    AA_SAMPLES.push_back(vec2(0, 0));

    AA_SAMPLES.push_back(vec2( hp * lcos,  hp * lsin));
    AA_SAMPLES.push_back(vec2(-hp * lcos, -hp * lsin));
    AA_SAMPLES.push_back(vec2(-hp * lcos,  hp * lsin));
    AA_SAMPLES.push_back(vec2( hp * lcos, -hp * lsin));

    AA_SAMPLES.push_back(vec2( hp * rcos,  hp * rsin));
    AA_SAMPLES.push_back(vec2(-hp * rcos, -hp * rsin));
    AA_SAMPLES.push_back(vec2(-hp * rcos,  hp * rsin));
    AA_SAMPLES.push_back(vec2( hp * rcos, -hp * rsin));
}

// Metode principal del programa

int main(int argc, char **argv) {

    // inicialitza l'escena: el constructor de l'escena s'encarrega de
    // crear els objectes i les llums
    scene = new Scene();

    initSuperSamplingAA();

    int pixels = scene->cam->viewportX * scene->cam->viewportY;
    FRAME_BUFFER = (vec3**)malloc(sizeof(vec3*) * pixels);
    for(int i = 0; i < pixels; i++)
        FRAME_BUFFER[i] = new vec3;

#ifdef GLUT

    //inicialitza OpenGL
	glutInit(&argc, argv);
    //Define la mida de la window GL especificada per la mida del viewport
    glutInitWindowSize(scene->cam->viewportX, scene->cam->viewportY);

    //Creacio de la window per pintar amb GL
	glutCreateWindow("RayTracer");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	

    //Posa la funcio Render per a que la window GL cridi quan es refresca
    glutDisplayFunc(Render_omp);
	atexit(cleanup);

    // Inicia el main loop per a poder refrescar l'escena
    glutMainLoop();
#else
    Render();
#endif

    return 0;
}
