#include "Cube.h"

/**
 * @brief Cube::Cube
 * Axis Aligned Voxel Cube
 */
Cube::Cube(vec3 orig, float hw, Material* m) : Object(m){
    origin = orig;
    halfwidth = hw;
    // Bounds
    bmin = origin - vec3(hw, hw, hw);
    bmax = origin + vec3(hw, hw, hw);

    forward = vec3(0,0,1);
    right = vec3(1,0,0);
    up = vec3(0,1,0);
}


bool Cube::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    // Intersection Points on 3 coordinates
    //float t0x, t1x, t0y, t1y, t0z, t1z;
    float tmin, tmax;


    // X Axis
    tmin = (bmin.x - r.origin.x) / r.direction.x;
    tmax = (bmax.x - r.origin.x) / r.direction.x;

    if(tmin > tmax) swap(tmin, tmax);


    // Y Axis
    float tymin = (bmin.y - r.origin.y) / r.direction.y;
    float tymax = (bmax.y - r.origin.y) / r.direction.y;

    if(tymin > tymax) swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;


    // Z Axis

    float tzmin = (bmin.z - r.origin.z) / r.direction.z;
    float tzmax = (bmax.z - r.origin.z) / r.direction.z;

    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;


    // Last Check

    if(tmin > t_min && tmax < t_max){
        // Detect face normal
        float maxcos = 0.7017;
        vec3 raynorm = normalize(r.direction);
        float fdot = dot(raynorm, forward);
        float rdot = dot(raynorm, right);
        float udot = dot(raynorm, up);

        if(fdot > maxcos){
            info.normal = forward;
            printf("forward");
        }
        if(fdot < -maxcos)
            info.normal = -forward;
        if(rdot > maxcos){
            printf("right");
            info.normal = right;
        }
        if(rdot < -maxcos)
            info.normal = -right;
        if(udot > maxcos){
            printf("up");
            info.normal = up;
        }
        if(udot < -maxcos)
            info.normal = -up;


        // Intersection is valid, fill in info
        info.t = tmin;
        info.p = r.origin + (r.direction * tmin);
        info.mat_ptr = material;

        return true;
    }

    return false;

}

