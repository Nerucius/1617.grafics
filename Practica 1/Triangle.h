#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"

class Triangle : public Object
{
public:
    Triangle(vec3, vec3, vec3, Material*);
    ~Triangle() {}
    bool hit(const Ray&, float t_min, float t_max, HitInfo&) const;
private:
        // Vectors
        vec3 v1, v2, v3;
};

#endif // TRIANGLE_H
