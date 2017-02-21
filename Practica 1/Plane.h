#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane: public Object  {
public:
        Plane(vec3, vec3, Material*);
        ~Plane() {}
        bool hit(const Ray&, float t_min, float t_max, HitInfo&) const;
private:
        // Origen del pla
        vec3 origin;
        // Definició per dos lines linealment independents
        vec3 normal;

};

#endif // PLANE_H
