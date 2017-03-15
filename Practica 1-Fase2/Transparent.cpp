#include "Transparent.h"

Transparent::Transparent(const vec3& diff):Material()
{
    Kd = diff;
}

Transparent::Transparent(const vec3 &amb, const vec3 &diff, const vec3 &spec, float _as, float _alpha){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    beta = _as;
    alpha = _alpha;
    n = 1.33;
}

Transparent::~Transparent(){}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    float nit = 1.003f / n;
    float cosT = sqrt(1 - nit*nit);

    vec3 N = rec.normal;
    vec3 L = r_in.direction;

    vec3 target = rec.p;
    target += - nit * L + N * (nit * cosT) - sqrt(1 - nit*nit *(1 - cosT * cosT ));

    scattered = Ray(rec.p, normalize(target-rec.p));
    color = Kd;
    return true;
}
