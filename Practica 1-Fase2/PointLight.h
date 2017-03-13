#pragma once
#include "glm/glm.hpp"

using namespace glm;

class PointLight {

public:
    PointLight(const vec3&, const vec3&, const vec3& ,const vec3& , const vec3& );
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


