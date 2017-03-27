#include "Transparent.h"


Transparent::Transparent(const vec3 &amb, const vec3 &diff, const vec3 &spec, const vec3& Kt, float n){
    Ka = amb;
    Kd = diff;
    Ks = spec;
    this->Kt = Kt;
    this->n = n;
    this->shininess = 0;
    this->beta = 0;
}

Transparent::~Transparent(){}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    // Use air's n as a constant
    float nfactor = 1.0003 / n;

    vec3 N = normalize(rec.normal);
    vec3 I = normalize(r_in.direction);
    // Flip Normal and n ratio when going through face from behind
    if(dot(I , N) > 0 ){
        N = -N;
        nfactor = 1./nfactor;
    }

    vec3 R = refract(I, N, nfactor);
    scattered = Ray(rec.p, R);
    color = Kt;

    // If the angle is too extreme, this function returns (0,0,0)
    // And so the light is reflected instead of refracting
    if(R.x * R.x + R.y * R.y + R.z * R.z < 0.1f){
        scattered = Ray(rec.p, reflect(I, N));
        color = Ks;

    }

    return true;
}
