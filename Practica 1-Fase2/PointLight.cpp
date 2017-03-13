#include "PointLight.h"

// I

PointLight::PointLight(const vec3& _pos, const vec3& amb,const vec3& dif, const vec3& spec,const vec3& _coef){

    pos = _pos;
    Ia = amb;
    Id = dif;
    Is = spec;
    coef = _coef;

}
