#include "Triangle.h"

Triangle::Triangle(vec3 _v1, vec3 _v2, vec3 _v3, Material* m) : Object(m){
    v1 = _v1;
    v2 = _v2;
    v3 = _v3;
}

bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    // Black magic equations

    vec3 e1,e2,h,s,q;
    float t,a,f,u,v;

    e1 = v2 - v1;
    e2 = v3 - v1;

    h = cross(r.direction, e2);
    a = dot(e1, h);

    if (abs(a) < 0.00001)
        return false;

    f = 1/a;
    s = r.origin - v1;
    u = f * dot(s,h);

    if (u < 0. || u > 1.)
        return false;

    q = cross(s, e1);
    v = f * dot(r.direction, q);

    if(v < 0. || u+v > 1.)
        return false;

    t = f * dot(e2, q);

    if (t > t_min+0.00001 && t < t_max){
        info.p = r.origin + (r.direction * t);
        info.t = t;
        info.mat_ptr = material;
        info.normal = vec3(0,0,0);

        return true;
    }

    return false;

}
