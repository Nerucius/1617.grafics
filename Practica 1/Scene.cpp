#include "Scene.h"
#include <stdlib.h>


Scene::Scene()
{
    // creacio de la camera
    //vec3 lookfrom(0, 1.8, 25);
    vec3 lookfrom(20,10,20);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = 1280;
    int pixelsY = 720;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

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
        }
    }
    delete cam;
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {


    //objects.push_back(new Sphere(vec3(-1 , 0.9  , 0), 1, new Lambertian(vec3(1, 0.8, 1))));
    //objects.push_back(new Sphere(vec3(0  , 1, 0), 1, new Lambertian(vec3(1, 0.6, 1))));
    //objects.push_back(new Sphere(vec3(1.5, 0.9  , 0), 1, new Lambertian(vec3(1, 0.4, 1))));

    // Planes
    vec3 grass = vec3(0.6, 0.85, 0.5);
    vec3 sky =   vec3(0.5, 0.7, 1.0);
    vec3 darkgray =  vec3(0.4, 0.4, 0.4);
    vec3 gray =  vec3(0.5, 0.5, 0.5);
    vec3 lightgray =  vec3(0.65, 0.65, 0.65);
    vec3 white =  vec3(1, 1, 1);
    vec3 green =  vec3(0.2, 0.9, 0.2);

    objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), new Lambertian(lightgray) ) );
    objects.push_back(new Plane(vec3(0,0,0), vec3(1,0,0), new Lambertian(darkgray) ) );
    objects.push_back(new Plane(vec3(0,0,0), vec3(0,0,1), new Lambertian(gray) ) );

    vec3 v1 = vec3(0,0, 3);
    vec3 v2 = vec3(3,5, 1);
    vec3 v3 = vec3(6,0, -1);

    objects.push_back(new Triangle(v1,v2,v3, new Lambertian(green) ) );


    //objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), new Lambertian(grass) ) );
    //objects.push_back(new Plane(vec3(10,0,0), vec3(-1,0,1), new Lambertian(gray) ) );
    //objects.push_back(new Plane(vec3(0,0,-10), vec3(0,0,1), new Lambertian(sky) ) );

//  objects.push_back(new BoundaryObject("../RayTracing201617/resources/peo1K.obj", new Lambertian(vec3(0.2, 0.6, 0.8))));

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
        closest->hit(raig, t_min,t_max, info);
        return true;
    }

    return false;
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

    if(Scene::hit(ray, t_min, t_max, *info)){
        return info->mat_ptr->diffuse /*+ info->normal*0.3f*/;
    }


    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.

       Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
       hitInfo ha d'anar tenint el color actualitzat segons els rebots.
    */
     //color = 0.5f*vec3(ray.direction.x+1, ray.direction.y+1, ray.direction.z+1);

     return vec3(1,0,0);
     float factor = (ray.direction.y + 2) * 0.25;

     vec3 bluefactor = vec3(0.5,0.7,1.) * factor;
     vec3 whitefactor = vec3(1,1,1) * (1-factor);

     return bluefactor + whitefactor;

}

