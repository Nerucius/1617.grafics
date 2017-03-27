#include "Lambertian.h"

Lambertian::Lambertian(const vec3& diff):Material()
{
    Kd = diff;
    Ka = vec3(0);
    Ks = vec3(0);
}

Lambertian::Lambertian(const vec3 &amb, const vec3 &diff, const vec3 &spec, float shininess, float beta){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    this->shininess = shininess;
    this->beta = beta;
}

Lambertian::~Lambertian(){}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    scattered = Ray(rec.p, normalize(target-rec.p));
    color = Kd;
    return true;
}

