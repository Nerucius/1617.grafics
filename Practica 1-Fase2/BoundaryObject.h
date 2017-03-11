#pragma once

#include <vector>
#include <string>

#include <iostream>
#include <stdlib.h>
#include <string>

#include "Object.h"
#include "Cara.h"
#include "ReadFile.h"
#include "Triangle.h"
#include "Cube.h"

using namespace std;

class BoundaryObject : public Object
{
public:
    BoundaryObject(string s, vec3, Material *m);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    virtual ~BoundaryObject();

private:


    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<Triangle*> triangles; // llista de Triangle, representant cadascun una cara
    Cube* bounds;

    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);

};
