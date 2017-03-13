#pragma once
#include "glm/glm.hpp"

using namespace glm;

class PointLight {

public:
    PointLight(const vec3& pos, const vec3& amb,const vec3& dif, const vec3& spec,const vec3& coef);
    ~PointLight(){}

    vec3 pos;
    /*
     * Ia - ambient light color
     * Id - diffuse light color
     * Is - specular light color
     * */
    vec3 Ia, Id, Is;
    vec3 coef;


};


