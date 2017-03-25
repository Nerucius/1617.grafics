#pragma once

#include "glm/glm.hpp"
using namespace glm;

class Scene;

class Light {

public:
    Light();
    ~Light();
    virtual float visible(Scene* scene,
                          const vec3& pos) = 0;

    vec3 pos;
    vec3 coef;
    vec3 Ia, Id, Is;

};


