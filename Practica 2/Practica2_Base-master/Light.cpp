#include "Light.h"
#include<stdio.h>

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    //printf("%d\n", t);
}

vec4 Light::getPosition() const {
    return this->pos;
}

void Light::setPosition(const vec4& v) {
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
    this->coef = value;
}

bool Light::isActive() const {
    return this->active;
}

void Light::setActive(bool value){
    this->active = value;
}

LightType Light::getTipusLight() const {
    return this->type;
}

void Light::setTipusLight(const LightType &value){
    this->type = value;
}
