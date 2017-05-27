#pragma once
#include "Light.h"

#include <vector>

class AreaLight : public Light{

public:
    AreaLight(const vec3& pos,
               const float radius,
               const int n,
               const vec3& amb,
               const vec3& dif,
               const vec3& spec,
               const vec3& coef);
    ~AreaLight(){}
    float visible(Scene* scene,
                  const vec3& pos) override;

private:
    std::vector<vec3*> points;
    int num_lights;
};


