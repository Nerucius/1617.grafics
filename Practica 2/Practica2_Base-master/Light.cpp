#include "Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getDiffuseIntensity() {
    return this->id;
}

/**
 * @brief Light::setDiffuseIntensity
 * @param i
 */
void Light::setDiffuseIntensity(vec3 i) {
    this->id = i;
}
vec4 Light::getLightPosition() {
    return this->pos;
}

void Light::setLightPosition(vec4 v) {
    this->pos = v;
}

void Light::switchOnOff() {
    this->active = !this->active;
 }

vec3 Light::getIa() const {
    return this->ia;
}

void Light::setIa(const vec3 &value) {
    this->ia = value;
}

vec3 Light::getId() const {
    return this->id;
}


void Light::setId(const vec3 &value) {
    this->id = value;
}

vec3 Light::getIs() const {
       return this->is;
}

void Light::setIs(const vec3 &value) {
    this->is = value;
}

vec3 Light::getCoeficients() const {
    return this->coef;
}

void Light::setCoeficients(const vec3 &value) {
    // TO DO: A canviar a la fase 1 de la practica 2
    // el float que es rep ha de multiplicar els tres valors de la intensitat difusa de la Light
    this->coef = value;
}

bool Light::getEstaActivat() const {
    return this->active;
}

void Light::setEstaActivat(bool value){
    this->active = value;
}

LightType Light::getTipusLight() const {
    // TO DO: A canviar a la fase 1 de la practica 2
    return Puntual;
}

void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
}
