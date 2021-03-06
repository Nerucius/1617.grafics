#include "BoundaryObject.h"
#include <string.h>

BoundaryObject::BoundaryObject(string s, vec3 offset, Material *m) : Object(m)
{ 

  readObj(s);
  // TODO: Cal fer un recorregut de totes les cares per a posar-les com Triangles
  // Cal recorrer l'estructura de l'objecte segons cara-vertexs que es carrega
  triangles.clear();

  vec3 bmin;
  vec3 bmax;

  //vec3 offset = vec3(23, 7.8, 5);

  for(Cara c : cares){
      // Read face and load each of the face's vertices
      vec3 v0 = vec3(vertexs[c.idxVertices[0]]) + offset;
      vec3 v1 = vec3(vertexs[c.idxVertices[1]]) + offset;
      vec3 v2 = vec3(vertexs[c.idxVertices[2]]) + offset;

      // find min and max vertices
      bmin = min(v0, bmin);
      bmax = max(v0, bmax);

      //Material* newMat = new Lambertian(m->diffuse);
      Triangle* t = new Triangle(v0, v1, v2, m);

      // SigSegv here on some faces????
      triangles.push_back(t);
  }

  bounds = new Cube(bmin, bmax, m);

  vertexs.clear();
  cares.clear();
}

BoundaryObject::~BoundaryObject() {

}

bool BoundaryObject::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    // Bounds check
    if(!bounds->hit(r, t_min, t_max,rec))
        return false;

    HitInfo close;
    close.t = HUGE_VALF;

    for(Triangle* t : triangles)
        if(t->hit(r, t_min,t_max, rec))
               if(rec.t < close.t)
                    close = rec;



    if(close.t != HUGE_VALF){
        rec = close;
        return true;
    }

  return false;
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename){

    FILE *fp = fopen(filename.c_str(),"rb");
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
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                string sx(ReadFile::words[1]);
                string sy(ReadFile::words[2]);
                string sz(ReadFile::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadFile::words[4]);
                    double w = atof(sw.c_str());
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, 0);
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
        fclose(fp);
    }
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void BoundaryObject::construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
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
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}
