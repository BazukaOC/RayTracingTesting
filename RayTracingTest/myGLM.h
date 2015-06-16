#ifndef MYGLM_H_INCLUDED
#define MYGLM_H_INCLUDED

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#define GLM_NONE     (0)                /* render with only vertices */
#define GLM_FLAT     (1 << 0)           /* render with facet normals */
#define GLM_SMOOTH   (1 << 1)           /* render with vertex normals */
#define GLM_TEXTURE  (1 << 2)           /* render with texture coords */
#define GLM_COLOR    (1 << 3)           /* render with colors */
#define GLM_MATERIAL (1 << 4)           /* render with materials */

typedef unsigned int GLuint;
typedef float GLfloat;
typedef void GLvoid;


typedef struct _GLMmaterial
{
    char*         name;                 /* name of material */
    float         diffuse[4];           /* diffuse component */
    float         ambient[4];           /* ambient component */
    float         specular[4];          /* specular component */
    float         emmissive[4];         /* emmissive component */
    float         shininess;            /* specular exponent */
    unsigned int  textureID;
} GLMmaterial;

typedef struct _GLMtriangle {
    unsigned int  vindices[3];          /* array of triangle vertex indices */
    unsigned int  nindices[3];          /* array of triangle normal indices */
    unsigned int  tindices[3];          /* array of triangle texcoord indices*/
    unsigned int  findex;               /* index of triangle facet normal */
} GLMtriangle;

typedef struct _GLMgroup {
    char*         name;                 /* name of this group */
    unsigned int  numtriangles;         /* number of triangles in this group */
    unsigned int* triangles;            /* array of triangle indices */
    unsigned int  material;             /* index to material for group */
    struct _GLMgroup* next;             /* pointer to next group in model */
} GLMgroup;

typedef struct _GLMmodel {
    char*          pathname;            /* path to this model */
    char*          mtllibname;          /* name of the material library */

    unsigned int   numvertices;         /* number of vertices in model */
    float*         vertices;            /* array of vertices  */

    unsigned int   numnormals;          /* number of normals in model */
    float*         normals;             /* array of normals */

    unsigned int   numtexcoords;        /* number of texcoords in model */
    float*         texcoords;           /* array of texture coordinates */

    unsigned int   numfacetnorms;       /* number of facetnorms in model */
    float*         facetnorms;          /* array of facetnorms */

    unsigned int   numtriangles;        /* number of triangles in model */
    GLMtriangle*   triangles;           /* array of triangles */

    unsigned int   nummaterials;        /* number of materials in model */
    GLMmaterial*   materials;           /* array of materials */

    unsigned int   numgroups;           /* number of groups in model */
    GLMgroup*      groups;              /* linked list of groups */

    float          position[3];         /* position of the model */

} GLMmodel;

/* glmUnitize: "unitize" a model by translating it to the origin and
 * scaling it to fit in a unit cube around the origin.  Returns the
 * scalefactor used.
 *
 * model - properly initialized GLMmodel structure
 */
GLfloat
glmUnitize(GLMmodel* model);

/* glmReadOBJ: Reads a model description from a Wavefront .OBJ file.
 * Returns a pointer to the created object which should be free'd with
 * glmDelete().
 *
 * filename - name of the file containing the Wavefront .OBJ format data.
 */
GLMmodel*
glmReadOBJ(char* filename);

#endif // MYGLM_H_INCLUDED
