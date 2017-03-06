#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

class Cube : public Object{
public:
    Cube(vec3 origin, float halfwidth, Material*);
    Cube(vec3 bmin, vec3 bmax, Material*);
    ~Cube(){}
    bool hit(const Ray&, float t_min, float t_max, HitInfo&) const;
private:
    // origin and half-width
    // origin is defined as CENTER of cube.
    vec3 origin, bmin, bmax;
    // Face normals
    vec3 forward, right, up;
    float halfwidth;

    /** Swap two floats, for hit detection */
    static void swap(float& a, float& b){
        float t = b;
        b = a;
        a = t;
    }

    /** Swap two floats, for hit detection */
    static bool equals(float a, float b, float e){
        return fabs(a-b) < e;
    }

};

#endif // CUBE_H
