#include "Metallic.h"

Metallic::Metallic(const vec3& diff):Material()
{
    Kd = diff;
}

Metallic::Metallic(const vec3 &amb, const vec3 &diff, const vec3 &spec, float _as, float _alpha){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    beta = _as;
    alpha = _alpha;
}

Metallic::~Metallic(){}

bool Metallic::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    // Manual reflection
    //vec3 d = rec.p - r_in.origin;
    //vec3 target = d - 2 * dot(d , rec.normal) * rec.normal;
    //target += RandomInSphere() * fuzzy;
    //scattered = Ray(rec.p, normalize(target-rec.p));

    // GLM library
    vec3 R = reflect(normalize(r_in.direction), normalize(rec.normal));
    scattered = Ray(rec.p, R);

    color = Ks;
    return true;
}
