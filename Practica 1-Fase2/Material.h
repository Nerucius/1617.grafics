#ifndef MATERIAL_H
#define MATERIAL_H


#include "Ray.h"
#include "Hitable.h"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();
    ~Material();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const = 0;

    vec3 Ka, Kd, Ks;
    float as = 1, alpha = 1;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
