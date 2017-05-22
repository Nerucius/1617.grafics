#include <Object.h>
#include <readfile.h>

/**
 * @brief Object::Object
 * @param npoints
 * @param parent
 */
Object::Object(int npoints, QObject *parent, Material* mat) : QObject(parent){
    numPoints = npoints;
    points = new point4[numPoints];
    normals= new point4[numPoints];

    this->material = mat;

 }

Object::Object(int npoints, QString path, Material* mat) : numPoints(npoints){
    points = new point4[numPoints];
    normals= new point4[numPoints];

    this->material = mat;

    // Init texture arrays
    for(int i = 0; i<4; i++){
        this->enTexture[i] = 0;
        this->texMaps[i] = NULL;
    }

    readObj(path);
    make();
}


/**
 * @brief Object::~Object
 */
Object::~Object(){
    delete points;
    delete normals;
}

/**
 * @brief Object::toGPU
 * @param pr
 */
void Object::toGPU(QGLShaderProgram *pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals

    program = pr;

    // Crear Vertex Buffer, amb tants elements com necesitem per les dades:
    // v4f x totes les posicions dels vertex
    // v4f x totes les normals dels vertex
    // v2f x totes les cordenades de textura dels vertex? -> NO HO USAREM
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER,
                  sizeof(vec4)*Index + sizeof(vec4)*Index,
                  NULL,
                  GL_STATIC_DRAW );

    glEnable(GL_DEPTH_TEST);

}


/**
 * Pintat en la GPU.
 * @brief Object::draw
 */
void Object::draw(){
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU

    // Aqui es torna a repetir el pas de dades a la GPU per si hi ha més d'un objecte
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Seleccionar zona del buffer de 0 a numero de vertex, copiar les dades
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    // Posició de memoria de la GPU que correspon a vPosition
    int vertexLocation = program->attributeLocation("vPosition");
    // Marcar com "Attribute Array" per cada vertex
    program->enableAttributeArray(vertexLocation);
    // Aquest atribut del vertex es dirà "vPosition", i es salta de 4 en 4 per vertex
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    // Activar Normals
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &normals[0] );
    int normalLocation = program->attributeLocation("vNormal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, 0, 4);


    // Send Material attributes to GPU
    material->toGPU(program);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, this->Index );
}

/**
 * @brief Object::make
 */
void Object::make(){

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            normals[Index] = vNormals[cares[i].idxVertices[j]];
            //colors[Index] = vec4(base_colors[j%4], 1.0);
            Index++;
        }
    }
}


void Object::initTextura(char* imagePath, TexSlot slot){
    // Activar textures

    glActiveTexture(GL_TEXTURE0 + slot);
    this->texMaps[slot] = new QOpenGLTexture(QImage(imagePath));
    this->texMaps[slot]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    this->texMaps[slot]->setMagnificationFilter(QOpenGLTexture::Linear);
    this->texMaps[slot]->bind(slot);

    this->enTexture[slot] = 1;

    cout << "Init Texture Slot: " << slot << endl;
}



/**
 * @brief Object::toGPUTexture
 * @param pr
 */
void Object::toGPUTexture(QGLShaderProgram *program) {

    program->setUniformValue("hasNorm", 0);
    program->setUniformValue("hasSpec", 0);
    program->setUniformValue("hasEmissive", 0);

    if(this->enTexture[TexSlot::Diffuse]){
        this->texMaps[TexSlot::Diffuse]->bind(0);
        program->setUniformValue("diffTex", 0);
    }

    if(this->enTexture[TexSlot::Normal]){
        this->texMaps[TexSlot::Normal]->bind(1);
        program->setUniformValue("normTex", 1);
        program->setUniformValue("hasNorm", 1);
    }

    if(this->enTexture[TexSlot::Specular]){
        this->texMaps[TexSlot::Specular]->bind(2);
        program->setUniformValue("specTex", 2);
        program->setUniformValue("hasSpec", 1);
    }
    if(this->enTexture[TexSlot::Emissive]){
        this->texMaps[TexSlot::Emissive]->bind(3);
        program->setUniformValue("emissiveTex", 3);
        program->setUniformValue("hasEmissive", 1);
    }

    this->toGPU(program);

    // Enable texturing on any
    if(this->enTexture[TexSlot::Diffuse]
            || this->enTexture[TexSlot::Normal]
            || this->enTexture[TexSlot::Specular]
            || this->enTexture[TexSlot::Emissive]){

        glEnable(GL_TEXTURE_2D);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

}


/**
 * Pintat en la GPU.
 * @brief Object::drawTexture
 */
void Object::drawTexture(){
    this->draw();
}



// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic Object.
void Object::readObj(QString filename){

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                // VERTEX COORDINATES

                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'Object
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
                // VERTEX NORMALS

                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }

                // S'afegeix la normal de vertex a l'Object
                vNormals.push_back(vec4(x, y, z, 0));

            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'Object
                // A modificar si es vol carregar mes de un Object
                construeix_cara (&ReadFile::words[1], nwords-1);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    // Calcul de les normals a cada cara
    for(unsigned int i=0; i<cares.size(); i++){
        cares[i].calculaNormal(vertexs);
    }
}

Capsa3D Object::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
    for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}



void Object::construeix_cara ( char **words, int nwords) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(this->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    this->cares.push_back(face);
}
