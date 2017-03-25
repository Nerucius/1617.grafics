#include "AreaLight.h"

#include "Scene.h"
#include "Ray.h"
#include "Hitable.h"

#include <cmath>

AreaLight::AreaLight(const vec3& _pos,
                       const float radius,
                       const int n,
                       const vec3& amb,
                       const vec3& dif,
                       const vec3& spec,
                       const vec3& _coef):Light()
{
    this->pos = _pos;
    this->Ia = amb;
    this->Id = dif;
    this->Is = spec;
    this->coef = _coef;
    this->num_lights = n;

    // Generate N points around the light pos for
    // visibility calculation
    // Points are on a flat X-Z plane
    float angleDelta = 360.f / n;
    for (int i = 0; i < n; i++){
        float angle = i * angleDelta;
        float sin_f = sin(angle * (M_PI/180.f));
        float cos_f = cos(angle * (M_PI/180.f));

        float x = pos.x + sin_f*radius;
        float y = pos.y;
        float z = pos.z + cos_f*radius;
        points.push_back(new vec3(x,y,z));
    }

}

float AreaLight::visible(Scene* scene, const vec3& pos){
    Ray r;
    HitInfo info;

    float visibility = 0;
    float val_per_light = 1.f / this->num_lights;

    for(vec3* light : points){
        r.origin = pos;
        r.direction = *light - pos;
        if(!scene->hit(r, 0.01, 1, info)){
            visibility += val_per_light;
        }
    }



    return visibility;
}
