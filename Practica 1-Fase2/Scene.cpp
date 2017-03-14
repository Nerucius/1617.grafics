#include "Scene.h"
#include <stdlib.h>


Scene::Scene()
{
    // creacio de la camera
    //vec3 lookfrom(0, 1.8, 25);
    vec3 lookfrom(2*1, 1.8*1, 12*1);
    vec3 lookat(0, 0, 0);

    float dist_to_focus = 10.0;
    float aperture = 0.1;

    int pixelsX = 720;
    int pixelsY = 460;

    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

    globalIa = vec3(.01, .01, .01);

   // TODO: Cal crear els objectes de l'escena
    RandomScene();

    // TODO: Cal afegir llums a l'escena (Fase 2)
   }

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);
            if (dynamic_cast<Plane*>(objects[i]))
                    delete (Plane *)(objects[i]);
            if (dynamic_cast<Triangle*>(objects[i]))vec3 lookfrom(0, 1.8, 25);
                    delete (Triangle *)(objects[i]);
            if (dynamic_cast<Cube*>(objects[i]))
                    delete (Cube *)(objects[i]);
        }
    }
    delete cam;
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {
    // Colors!
    vec3 white =      vec3(1, 1, 1);
    vec3 lightgray =  vec3(0.65, 0.65, 0.65);
    vec3 gray =       vec3(0.5, 0.5, 0.5);
    vec3 darkgray =   vec3(0.2, 0.2, 0.2);
    vec3 black =      vec3(0,0,0);
    vec3 lightgreen = vec3(0.6, 0.85, 0.5);
    vec3 green =      vec3(0.2, 0.8, 0.2);
    vec3 darkgreen =  vec3(0.2, 0.6, 0.2);
    vec3 lightblue =  vec3(0.5, 0.7, 1.0);
    vec3 blue =       vec3(0.4, 0.4, 0.8);
    vec3 darkblue =   vec3(0.3, 0.3, 0.6);
    vec3 lightred =   vec3(0.9,0.6,0.6);
    vec3 red =        vec3(0.9,0.4,0.4);
    vec3 darkred =    vec3(0.5,0.3,0.3);
    vec3 pink =       vec3(1,0,1);
    vec3 yellow =     vec3(0.8,0.8,0);


    // lights
    this->setAmbientLight( vec3(.01,.01,.01) );

    lights.push_back(new PointLight(
                         //cam->origin,
                         vec3( -4,  8, 10),
                         vec3( .1, .1, .1),
                         vec3( .5, .5, .5),
                         vec3(  1,  1,  1),
                         vec3( .5, .0,.01))
                     );

//    lights.push_back(new PointLight(
//                         vec3( 8,  8, 20),
//                         vec3( .1, .1, .1),
//                         vec3( .8, .2, .2),
//                         vec3(  1,  0,  0),
//                         vec3( .5,  0,.01))
//                     );


    // Spheres
    Lambertian* gray_shinny = new Lambertian(darkgray, gray, white, 50, 1);
    Lambertian* yellow_matte = new Lambertian(darkgray, yellow, gray, 5, 1);
    Lambertian* red_shiny = new Lambertian(darkgray, red, gray, 50, 1);

    objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, gray_shinny));
    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, yellow_matte));

    /*
    objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), new Lambertian(lightblue) ) );
    objects.push_back(new Plane(vec3(-5,0,0), vec3(1,0,0), new Lambertian(lightred) ) );
    objects.push_back(new Plane(vec3(0,0,-5), vec3(0,0,1), new Lambertian(lightgreen) ) );

    vec3 v1 = vec3(0,0, 3);
    vec3 v2 = vec3(3,5, 1);
    vec3 v3 = vec3(6,0, -1);
    objects.push_back(new Triangle(v1,v2,v3, new Lambertian(lightgreen) ) );
    */
    //string filepath = string("../Practica 1/resources/peo1K.obj");
    //objects.push_back(new BoundaryObject(filepath, vec3(23, 7.8, 5), gray_shinny));
    //*/

}

void Scene::setAmbientLight(const vec3& color){
    this->globalIa = color;
}

/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena (Fase 1)
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode hit per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.


    float closestDist = t_max+1;
    Hitable* closest = 0;

    for (uint i = 0; i < objects.size(); i++){
        Hitable* obj = objects[i];

        if (obj->hit(raig, t_min, t_max, info)){
            //float dist = length(info.p - cam->origin);
            if(info.t < closestDist){
                closest = obj;
                closestDist = info.t;
            }
        }

    }

    if(closest){
        closest->hit(raig, t_min, t_max, info);
        return true;
    }

    return false;
}



vec3 Scene::BlinnPhong(vec3 point, vec3 N, const Material* mat, bool shadow){
    // Always add global Ia
    vec3 color = vec3(0,0,0) + globalIa;

    HitInfo info;

    vec3 V = normalize(cam->origin - point);
    for(PointLight* l : lights){

        // Shadow Ray Calculation
        if(shadow){
            Ray r;
            r.origin = point;
            r.direction = l->pos - point;
            if(Scene::hit(r, 0.01, 1, info)){
                color += (mat->Ka * l->Ia);
                continue;
            }
        }

        // Light -> Camera
        vec3 L = (l->pos - point);

        // Attenuation factor
        float d2 = L.x * L.x + L.y * L.y + L.z + L.z;
        float attf = 1. / (l->coef.x + l->coef.y * 0 + l->coef.z * d2);

        L = normalize(L);
        // Half vector between light->cam and pos->cam
        vec3 H = normalize(L + V);

        //vec3 R = normalize(2 * dot(L, N) * (N - L));
        //float costheta = dot(R, V);

        color = color
                 + (mat->Ka * l->Ia) * attf// Ambient
                 + (mat->Kd * l->Id * (dot(L, N))) * attf// Diffuse
                 + (mat->Ks * l->Is * pow(dot(N, H), mat->as)) * attf // Specular
                ;
    }
    return color;

}

/*
** TODO: Funcio ComputeColor es la funcio recursiva del RayTracing.
** A modificar en la Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en la Fase 2 per a tractar reflexions
**
*/


vec3 Scene::ComputeColor (Ray &ray, int depth ) {

    vec3 color;
    // Define near and far planes
    float t_min = 0.1;
    float t_max = 100;
    HitInfo* info = new HitInfo;

    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.
     */

    if(Scene::hit(ray, t_min, t_max, *info)){
        return Scene::BlinnPhong(info->p, info->normal, info->mat_ptr, true);
    }

    // Background
    float factor = (ray.direction.y + 2) * 0.5;

    vec3 bluefactor = vec3(0.5,0.7,1.) * factor;
    vec3 whitefactor = vec3(1,1,1) * (1-factor);

    return bluefactor + whitefactor;

}


