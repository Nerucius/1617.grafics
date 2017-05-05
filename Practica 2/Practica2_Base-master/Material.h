#ifndef MATERIAL_H
#define MATERIAL_H

#include <Common.h>
#include <QGLShaderProgram>

// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material(const vec3& Ka, const vec3& Kd, const vec3& Ks, float shine);

    void toGPU(QGLShaderProgram *program);

    vec3 Ka, Kd, Ks;
    float shine;
};

#endif // MATERIAL_H
