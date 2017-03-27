#include "Scene.h"

Scene::Scene()
{
    // creacio de la camera
    //vec3 lookfrom(0, 1.8, 25);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);

    float dist_to_focus = 10.0;
    float aperture = 0.1;

    int pixelsX = 640;
    int pixelsY = 400;

    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

    globalIa = vec3(.01, .01, .01);

    //RandomScene();
    this->InitScene();

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

void Scene::InitScene(){
    this->cam = new Camera(vec3(-20,5,20), vec3(0), vec3(0,1,0), 20,600,300,.1,100);
    this->setAmbientLight(vec3(.2));

    // lights
    lights.push_back(new PointLight(
                         vec3(0,5,0),
                         vec3(.2),
                         vec3( .5),
                         vec3( .4),
                         vec3(0))
                     );

    // Materials
    Material* blue_metallic = new Metallic(vec3(.1), vec3(0,0,1), vec3(.4), 75, 1);
    Material* green_metallic = new Metallic(vec3(.1), vec3(0,1,0), vec3(.4), 75, 1);
    Material* red_metallic = new Metallic(vec3(.1), vec3(1,0,0), vec3(.4), 75, 1);

    Material* white_matte = new Lambertian(vec3(.1), vec3(1), vec3(0), 5, 1);
    Material* red_matte = new Lambertian(vec3(.1), vec3(1,0,0), vec3(0), 5, 1);

    Material* transparent = new Transparent(vec3(.1), vec3(0), vec3(.8), vec3(.4), 1.75);

    objects.push_back(new Plane(vec3(3,0,0), vec3(-1,0,0), blue_metallic ) );
    objects.push_back(new Plane(vec3(0,-3,0), vec3(0,1,0), white_matte ) );
    objects.push_back(new Plane(vec3(0,0,-3), vec3(0,0,1), green_metallic ) );

    objects.push_back(new Triangle( vec3(-2,-1,0), vec3(0,2,0), vec3(2,-1,0), red_matte ));

    objects.push_back(new Sphere(vec3(0, 0, 5), 1, transparent));

    objects.push_back(new Cube(vec3(-4,-4,4), vec3(-2,1,6), red_metallic));


//    // Spheres
//    // Planet Sphere
//    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, planet));

//    // Matte Spehere
//    objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, gray_matte));

//    // Metallic Spehere
//    objects.push_back(new Sphere(vec3(-3, 1, 1), 1, metallic));

//    // Transparent Sphere
//    objects.push_back(new Sphere(vec3(0, .75, 0), 1, bubble));
//    //objects.push_back(new Sphere(vec3(0, .75, 0), -.97, bubble));


    //objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), new Lambertian(lightblue) ) );
    //objects.push_back(new Plane(vec3(-10,0,0), vec3(1,0,1), mirror ) );
    //objects.push_back(new Plane(vec3(0,0,-5), vec3(0,0,1), new Lambertian(lightgreen) ) );
    /*

    objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), red_matte ) );
    objects.push_back(new Plane(vec3(-7.5,0,0), vec3(1,0,0), perfect_mirror ) );
    objects.push_back(new Plane(vec3(0,0,-7.5), vec3(0,0,1), perfect_mirror ) );

    string filepath = string("../Practica 1/resources/peo1K.obj");
    objects.push_back(new BoundaryObject(filepath, vec3(23, 7.8, 5), black_metallic));

    vec3 v1 = vec3(0,0, 3);
    vec3 v2 = vec3(3,5, 1);
    vec3 v3 = vec3(6,0, -1);
    objects.push_back(new Triangle(v1,v2,v3, new Lambertian(lightgreen) ) );
    */
    //string filepath = string("../Practica 1/resources/peo1K.obj");
    //objects.push_back(new BoundaryObject(filepath, vec3(23, 7.8, 5), gray_shinny));
    //*/

}

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
    vec3 lightblue =  vec3(0.6, 0.6, 1.0);
    vec3 blue =       vec3(0.4, 0.4, 0.8);
    vec3 darkblue =   vec3(0.3, 0.3, 0.6);
    vec3 lightred =   vec3(0.9,0.6,0.6);
    vec3 red =        vec3(0.9,0.2,0.2);
    vec3 darkred =    vec3(0.5,0.3,0.3);
    vec3 pink =       vec3(1,0,1);
    vec3 yellow =     vec3(0.8,0.8,0);


    // lights
    this->setAmbientLight( vec3(.01,.01,.01) );

    lights.push_back(new AreaLight(
                         vec3(2,8,10),
                         //0, 1,
                         1.f, 16, // Increase the 2nd number to soften shadow
                         vec3( .4),
                         vec3( .5),
                         vec3(1.),
                         vec3( .5, 0, .01))
                     );

    // Materials!
    Material* mirror = new Metallic(darkblue, black, vec3(.8), 10, 1, 0.05);
    Material* perfect_mirror = new Metallic(darkblue, black, vec3(.8), 10, 1, 0);
    Material* water = new Transparent(vec3(0), vec3(0), vec3(1), vec3(0.90), 1.33);
    Material* diamond = new Transparent(vec3(0), vec3(0), vec3(1), vec3(0.99), 2.43);
    Material* blue_matte = new Lambertian(darkblue, blue, darkgray, 5, 1);
    Material* red_matte = new Lambertian(darkred, red, darkgray, 5, 1);
    Material* yellow_matte = new Lambertian(darkred, yellow, darkgray, 5, 1);
    Material* green_matte = new Lambertian(darkgreen, green, darkgray, 5, 1);
    Material* black_metallic = new Metallic(black, darkgray, darkgray, 5, 1);

    // Materials specified by the pdf
    Material* gray_matte = new Lambertian(vec3(.2), vec3(.5), vec3(1), 10, 1);
    Material* planet = new Lambertian(vec3(.2), vec3(.8,.8,0), vec3(.5), 10, 1);
    Material* metallic = new Metallic(vec3(.2), vec3(.7,.6,.5), vec3(0.6), 10, 1, 0);
    Material* bubble = new Transparent(vec3(0), vec3(0), vec3(1), vec3(.9), 1.33);


    // Spheres
    // Planet Sphere
    objects.push_back(new Sphere(vec3(0, -100.5, -1), 100, planet));

    // Matte Spehere
    objects.push_back(new Sphere(vec3(0, 0, -1), 0.5, gray_matte));

    // Metallic Spehere
    objects.push_back(new Sphere(vec3(-3, 1, 1), 1, metallic));

    // Transparent Sphere
    objects.push_back(new Sphere(vec3(0, .75, 0), 1, bubble));
    //objects.push_back(new Sphere(vec3(0, .75, 0), -.97, bubble));


    //objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), new Lambertian(lightblue) ) );
    //objects.push_back(new Plane(vec3(-10,0,0), vec3(1,0,1), mirror ) );
    //objects.push_back(new Plane(vec3(0,0,-5), vec3(0,0,1), new Lambertian(lightgreen) ) );
    /*

    objects.push_back(new Plane(vec3(0,0,0), vec3(0,1,0), red_matte ) );
    objects.push_back(new Plane(vec3(-7.5,0,0), vec3(1,0,0), perfect_mirror ) );
    objects.push_back(new Plane(vec3(0,0,-7.5), vec3(0,0,1), perfect_mirror ) );

    string filepath = string("../Practica 1/resources/peo1K.obj");
    objects.push_back(new BoundaryObject(filepath, vec3(23, 7.8, 5), black_metallic));

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

/**
 *  Intersects a ray with all objects of the scene, and returns the closest intersection, if any.
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

/** Returns true for any intersections. Used for shadows. */
bool Scene::hit_fast(const Ray& ray, float t_min, float t_max, HitInfo& info) const{
    for (uint i = 0; i < objects.size(); i++){
        Hitable* obj = objects[i];

        if (obj->hit(ray, t_min, t_max, info)){
            return true;
        }
    }
    return false;
}

/**
 * Computes the color of a single point on a surface, taking into the account the scene's lights.
 */
vec3 Scene::BlinnPhong(vec3 point, vec3 N, const Material* mat, bool shadow){
    vec3 color;

    //  Surface -> Camera
    vec3 V = normalize(cam->origin - point);

    // Iterate over every light
    for(Light* l : lights){

        // Light Visibility Calculation (hard / soft shadwos)
        // How much of the light reaches the object.
        float shade = 1;
        if(shadow){
            shade = l->visible(this, point);
            // OMBRES la seguent linea
            // REFLEXIO1 la seguent linea
            //if(shade < 0.9) return vec3(1,0,0);
        }

        // REFLEXIO1 la seguent linia
        //return mat->Kd;

        // Surface -> Light
        vec3 L = (l->pos - point);
        // Attenuation factor
        float d2 = L.x * L.x + L.y * L.y + L.z + L.z;
        float attf = 1.f / (l->coef.x + l->coef.y * 0 + l->coef.z * d2);
        attf = attf > 1 ? 1 : attf;

        L = normalize(L);

        // Half vector between light->cam and pos->cam
        vec3 H = normalize(L + V);

        vec3 La = (mat->Ka * l->Ia) ;
        vec3 Ld = (mat->Kd * l->Id * (dot(L, N))) * attf * shade;
        vec3 Ls = (mat->Ks * l->Is * pow(dot(N, H), mat->beta)) * attf * shade;

        color = La + Ld + Ls;
    }

    // Add global Ambient at the end
    return color + globalIa * mat->Ka;

}

/**
 * Computes the color output of a given Ray, bouncing the light `depth` times.
 */
vec3 Scene::ComputeColor (Ray &ray, int depth ) {
    vec3 color;
    // Define near and far planes
    float t_min = 0.01;
    float t_max = 50;
    HitInfo* info = new HitInfo;


    if(Scene::hit(ray, t_min, t_max, *info)){
        // Impact with scene object. calculate lighting
        // PHONG el ultim parametre a false
        // OMBRES el ultim parametre a true
        color = this->BlinnPhong(info->p, info->normal, info->mat_ptr, true);

        // REFLEXIO1 el seguent bloc
        //if(color.r > 0.999 && color.g < .001 && color.b < .001)
        //    return color;

        vec3 KColor;
        Ray scattered;
        info->mat_ptr->scatter(ray, *info, KColor, scattered);
        vec3 inverseKt = (vec3(1.f) - info->mat_ptr->Kt);

        if (depth > 0){
            color = inverseKt * color + KColor * this->ComputeColor(scattered, depth-1);

            // REFLEXIO1 la seguent linea
            //color = this->ComputeColor(scattered, 0);
        }


    }else{
        // Background
        float factor = (ray.direction.y + 2) * 0.5;
        vec3 bluefactor = vec3(0.5,0.7,1.) * factor;
        vec3 whitefactor = vec3(1,1,1) * (1-factor);
        color = bluefactor + whitefactor;
    }

    return color;
}

vec3 Scene::ComputeColorDistance(Ray &ray, int depth){
    // DISTANCE
    vec3 color;
    // Define near and far planes
    float t_min = 0.01;
    float t_max = 50;
    HitInfo* info = new HitInfo;


    if(Scene::hit(ray, t_min, t_max, *info)){

        float distance = length(info->p - ray.origin);
        color = 2.f * (vec3(1) / (1+distance));

        vec3 KColor;
        Ray scattered;
        info->mat_ptr->scatter(ray, *info, KColor, scattered);

        if (depth > 0){
            color = color * 2.f * this->ComputeColorDistance(scattered, depth-1);
        }

        return color;
    }

    return vec3(.2);
}


