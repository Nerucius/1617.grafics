#include "Scene.h"

Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;


    lightAmbientGlobal = vec3(0.05);

    Light* l = new Light(Puntual);
    l->setPosition(vec4(4,6,0,1));
    l->setActive(true);
    l->setIa( vec3(0.1) );
    l->setId( vec3(0.6) );
    l->setIs( vec3(0.3) );
    l->setCoeficients( vec3(0,0,0.08) );
    this->addLight(l);

//    Light* l2 = new Light(Puntual);
//    l2->setPosition(vec4(-1,1,0,1));
//    l2->setActive(true);
//    l2->setIa(vec3(0.05));
//    l2->setId(vec3(0.5,0,0));
//    l2->setIs(vec3(0));
//    this->addLight(l2);
}

Scene::~Scene() {
    elements.clear();
    lights.clear();
}


void Scene::addObject(Object *obj) {
    elements.push_back(obj);
    calculCapsaMinCont3DEscena();
}

void Scene::draw() {
    for(unsigned int i=0; i < elements.size(); i++){
        // NOTE: Object.draw() also sends the Material to the GPU
        elements.at(i)->draw();
    }
}

void Scene::drawTexture() {
    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->drawTexture();
    }
}

Light* Scene::getLightActual() {
    // TODO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

void Scene::setLightActual(Light* l){
    lights[lights.size()-1]=l;
}


void Scene::lightsToGPU(QGLShaderProgram *program){
// TODO: A implementar a la fase 1 de la practica 2

    for(uint i=0; i < this->lights.size(); i++){

        Light* l = this->lights.at(i);
        uint ltype = program->uniformLocation(QString("lights[%1].type").arg(i));
        glUniform1i(ltype, l->getTipusLight());

        uint lactive = program->uniformLocation(QString("lights[%1].enabled").arg(i));
        glUniform1i(lactive, l->isActive() ? 1 : 0);

        uint lia = program->uniformLocation(QString("lights[%1].ia").arg(i));
        glUniform3fv(lia, 1, l->getIa());
        uint lid = program->uniformLocation(QString("lights[%1].id").arg(i));
        glUniform3fv(lid, 1, l->getId());
        uint lis = program->uniformLocation(QString("lights[%1].is").arg(i));
        glUniform3fv(lis, 1, l->getIs());

        uint lpos = program->uniformLocation(QString("lights[%1].pos").arg(i));
        glUniform4fv(lpos, 1, l->getPosition());
        uint lcoef = program->uniformLocation(QString("lights[%1].coef").arg(i));
        glUniform3fv(lcoef, 1, l->getCoeficients());


    }

}

void Scene::addLight(Light *l) {
    lights.push_back(l);

}

void Scene::ambientToGPU(QGLShaderProgram *program){
    // TODO: A implementar a la fase 1 de la practica 2

    GLint ambientLocation = program->uniformLocation("ambientLight");
    glUniform3fv(ambientLocation, 1, this->lightAmbientGlobal);

}


void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (elements.size()==1) {
        capsaMinima = elements[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<elements.size(); i++) {
       c = elements[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}
