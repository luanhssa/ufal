
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"
#include "latimmodel.h"
#include "camera.h"

Camera cam;
LaTIMModel latim;

GLint WIDTH =1280;
GLint HEIGHT=720;

/***************************************************************/
GLfloat ligh0pos[]     = { 0.0, 20.0, 0.0, 0.5};
GLfloat light0color[]  = { 0.8, 0.8, 0.8, 1.0};
GLfloat ambientlight[] = { 0.1, 0.1, 0.1, 1.0};
GLfloat light0dir[]    = { 3.45, 1.0, 3.90, 1.0};
GLint   spot_light0    = 60;

GLfloat light1pos[]    = { 4.0, 2.9, 4.0, 1.0};
GLfloat light1color[]  = { 0.5, 0.5, 0.5, 1.0};
GLfloat light1dir[]    = { 2.0, 1.0, 2.0 , 1.0};
GLint   spot_light1    = 50;
GLfloat shininess[]  = {1000};

GLfloat colorless[]    = { 0.0, 0.0, 0.0, 1.0};

// Capacidade de brilho do material
GLfloat especular[4] = {0.5,0.5,0.5,1.0};
GLint especMaterial = 100;
/***************************************************************/

/***************************************************************/
/* Some <math.h> files do not define M_PI... */
#ifndef M_PI
#define M_PI 3.14159265
#endif

static float modelAmb[4] = {0.1, 0.1, 0.1, 1.0};

static float matAmb[4] = {0.1, 0.1, 0.1, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
//static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};

#define TWO_PI	(2*M_PI)
typedef struct lightRec {
  GLfloat amb[4];
  GLfloat diff[4];
  GLfloat spec[4];
  GLfloat pos[4];
  GLfloat spotDir[3];
  GLfloat spotExp;
  GLfloat spotCutoff;
  GLfloat atten[3];

  GLfloat trans[3];
  GLfloat rot[3];
  GLfloat swing[3];
  GLfloat arc[3];
  GLfloat arcIncr[3];
} Light;

#define NUM_LIGHTS 6
static Light spots[] =
{
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {2.0, 2.9, 1.95, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    2.0,
    80.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {2.0, 2.9, 3.9, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    3.0,
    60.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {2.0, 2.9, 5.85, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    3.0,
    80.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {5.0, 2.9, 1.95, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    3.0,
    80.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {5.0, 2.9, 3.9, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    3.0,
    80.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },
  {
    {0.1, 0.1, 0.1, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.8, 0.8, 0.8, 1.0},  /* specular */
    {5.0, 2.9, 5.85, 1.0},  /* position */
    {0.0, -3.0, 0.0},   /* direction */
    3.0,
    80.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 0.0, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  }
};

int spin = 0;
void animate() {
  spin += 0.5;
  if (spin > 360.0)
    spin -= 360.0;
  glutPostRedisplay();
}

/***************************************************************/
