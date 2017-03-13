#include "Lambertian.h"

Lambertian::Lambertian(const vec3& diff):Material()
{
    Kd = diff;
}

Lambertian::Lambertian(const vec3 &amb, const vec3 &diff, const vec3 &spec, float _as, float _alpha){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    as = _as;
    alpha = _alpha;
}

Lambertian::~Lambertian(){}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    scattered = Ray(rec.p, target-rec.p);
    color = Kd;
    return true;
}

