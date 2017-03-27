#pragma once

#include "Material.h"

class Transparent : public Material {

public:
    Transparent(const vec3 &amb, const vec3 &diff, const vec3 &spec, const vec3& Kt, float n);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

    float n;

};
