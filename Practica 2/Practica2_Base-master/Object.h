#ifndef Object_H
#define Object_H

#include <QObject>
#include <vector>
#include <Common.h>
#include <cara.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include "Material.h"

using namespace std;

typedef Common::vec4  point4;

// Classe que conte la representacio d'un Objecte: geometria, topologia, material i textures
class Object : public QObject {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;
    vector<vec4> vNormals;

    GLuint buffer;
    GLuint nBuffer;

    int     numPoints;
    point4 *points;
    point4 *normals;

    int Index; // index de control del numero de vertexs a passar a la GPU

    QGLShaderProgram *program;

public:

    Object(const int npoints, QObject *parent = 0, Material* material = 0);
    Object(const int npoints, QString n, Material* material);
    ~Object();

    virtual void readObj(QString filename);

    virtual void make();
    virtual void toGPU(QGLShaderProgram *p);
    virtual void toGPUTexture(QGLShaderProgram *pr);

    virtual void initTextura(char* diffPath, char* normPath, char* specPath);

    virtual void draw();
    virtual void drawTexture();

    Capsa3D calculCapsa3D();

    Material* material;

    QOpenGLTexture *diffTex = NULL;
    QOpenGLTexture *normTex = NULL;
    QOpenGLTexture *specTex = NULL;

    bool enNormMap = 0;
    bool enSpecMap = 1;

private:

    void construeix_cara ( char **words, int nwords);

};



#endif // Object_H
