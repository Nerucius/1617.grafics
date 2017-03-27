#pragma once

#include "Material.h"

class Metallic : public Material {

public:
    Metallic(const vec3& color);
    Metallic(const vec3 &amb, const vec3 &diff, const vec3 &spec, float shininess, float beta);
    Metallic(const vec3 &amb, const vec3 &diff, const vec3 &spec, float shininess, float beta, float fuzzy);
    virtual ~Metallic();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

    /** Relflection fuzziness */
    float fuzzy;

};
