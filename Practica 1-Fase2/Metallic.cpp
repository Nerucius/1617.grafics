#include "Metallic.h"

Metallic::Metallic(const vec3& diff):Material()
{
    Kd = diff;
    Ka = vec3(0);
    Ks = vec3(1);
}

Metallic::Metallic(const vec3 &amb, const vec3 &diff, const vec3 &spec, float shininess, float beta){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    Kt = vec3(1) - Ks;
    this->shininess = shininess;
    this->beta = beta;
    this->fuzzy = 0;
}

Metallic::Metallic(const vec3 &amb, const vec3 &diff, const vec3 &spec, float shininess, float beta, float fuzzy){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    this->shininess = shininess;
    this->beta = beta;
    this->fuzzy = 0;;
}

Metallic::~Metallic(){}

bool Metallic::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    // Manual reflection
    //vec3 d = rec.p - r_in.origin;
    //vec3 target = d - 2 * dot(d , rec.normal) * rec.normal;
    //target += RandomInSphere() * fuzzy;
    //scattered = Ray(rec.p, normalize(target-rec.p));

    // GLM library Reflection
    vec3 R = reflect(normalize(r_in.direction), normalize(rec.normal));
    vec3 fuzz = vec3(0);
    if(fuzzy > 0)
        fuzz = fuzzy * RandomInSphere();
    scattered = Ray(rec.p, R + fuzz);

    color = Ks;
    return true;
}
