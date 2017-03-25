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

    n = 2.43f;
    Kt = vec3(1) * 1.f;
}

Transparent::~Transparent(){}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    float nfactor = 1.0003 / n;
    //nfactor = 0.5f;

    vec3 N = normalize(rec.normal);
    vec3 I = normalize(r_in.direction);
    if(dot(I , rec.normal) > 0 )
        N = -N;

    // If the angle is too extreme, this function returns (0,0,0)
    // And so the light reflected instead of refracting
    vec3 R = refract(I, N, nfactor);
    if(length(R) < 0.5){
        scattered = Ray(rec.p, reflect(I, N));
        color = Ks;

    }else{
        scattered = Ray(rec.p, R);
        color = vec3(1) - Ks;
    }

    color = Kt;


    // Kt = 1 - Ks
    return true;
}
