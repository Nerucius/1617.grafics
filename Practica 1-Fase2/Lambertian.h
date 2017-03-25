#pragma once

#include "Material.h"

class Lambertian : public Material {

public:
    Lambertian(const vec3& color);
    Lambertian(const vec3 &amb,
               const vec3 &diff,
               const vec3 &spec,
               float _as,
               float _alpha);
    virtual ~Lambertian();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

};
