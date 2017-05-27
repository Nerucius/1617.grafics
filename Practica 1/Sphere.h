#ifndef SPHEREH
#define SPHEREH

#include "Object.h"

class Sphere: public Object  {
public:
        Sphere(vec3 cen, float r, Material *m);
        ~Sphere() {}
        bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
private:
        // Centre de l'esfera
        vec3 center;
        // Radi de l'esfera
        float radius;

};


#endif



