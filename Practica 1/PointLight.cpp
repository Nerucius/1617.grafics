#include "PointLight.h"

#include "Scene.h"
#include "Ray.h"
#include "Hitable.h"

PointLight::PointLight(const vec3& _pos,
                       const vec3& amb,
                       const vec3& dif,
                       const vec3& spec,
                       const vec3& _coef):Light()
{
    this->pos = _pos;
    Ia = amb;
    Id = dif;
    Is = spec;
    coef = _coef;
}

float PointLight::visible(Scene* scene, const vec3& pos){
    Ray r;
    HitInfo info;

    r.origin = pos;
    r.direction = this->pos - pos;

    /* We are setting the tmax param as 1 to make the detection range the
     * same as the distance to the light. */
    if(scene->hit_fast(r, 0.01, 1, info)){
        return 0;
    }

    return 1;
}
