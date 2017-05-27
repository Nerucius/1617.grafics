#pragma once
#include "Light.h"

class PointLight : public Light{

public:
    PointLight(const vec3& pos,
               const vec3& amb,
               const vec3& dif,
               const vec3& spec,
               const vec3& coef);
    ~PointLight(){}
    float visible(Scene* scene,
                  const vec3& pos) override;
};


