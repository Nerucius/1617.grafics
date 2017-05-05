#include "Material.h"


Material::Material(const vec3& Ka, const vec3& Kd, const vec3& Ks, float shine) {
    this->Ka = Ka;
    this->Kd = Kd;
    this->Ks = Ks;
    this->shine = shine;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(QGLShaderProgram *program){

    struct{
        GLuint ka;
        GLuint kd;
        GLuint ks;
        GLuint shine;
    } mat;

    mat.ka = program->uniformLocation("mat.ka");
    mat.kd = program->uniformLocation("mat.kd");
    mat.ks = program->uniformLocation("mat.ks");
    mat.shine = program->uniformLocation("mat.shine");

    glUniform3f(mat.ka, Ka.x, Ka.y, Ka.z);
    glUniform3f(mat.kd, Kd.x, Kd.y, Kd.z);
    glUniform3f(mat.ks, Ks.x, Ks.y, Ks.z);
    glUniform1f(mat.shine, shine);

}

