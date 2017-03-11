#include "Plane.h"

Plane::Plane(vec3 orig, vec3 norm, Material* m) : Object(m) {
    origin = orig;
    normal = normalize(norm);
}

bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {

    // Check that ray is not parallel with normal
    // (no plane intersection if true)
    float denom = dot(r.direction, normal);

    // Some Epsilon value
    if( abs(denom) > 0.0001){

        // Calculate t value
        float t = dot(origin - r.origin, normal) / denom;

        // Check for t boundaries
        if (t < t_max && t > t_min){
            info.p = r.origin + (r.direction * t);
            info.normal = normal;
            info.t = t;
            info.mat_ptr = material;
            return true;
        }

        return false;
    }
    return false;
}
