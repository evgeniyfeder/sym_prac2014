/* FILENAME: RENDER.H
 * PROGRAMMER: EF2
 * PURPOSE: 3D render declaration module.
 * LAST UPDATE: 10.06.2014
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "matr.h"

/* Type of declaration camera in world */
typedef struct
{
  VEC
    Loc,             /* Coordinates */
    Dir, Up, Right,  /* Orientation */
    At;              /* Point of view */
} ef2CAMERA;

/* Gometric object data type */
typedef struct tagef2GOBJ
{
  VEC *V;      /* array for vectors */
  INT NumOfV;  /* number of vectors */
  INT (*F)[3]; /* array for  */
  INT NumOfF;  /* number of  */
} ef2GOBJ;

/* Global camera */
extern ef2CAMERA EF2_RndCam;

/* Rnd parametrs */
extern DBL
  EF2_RndWs, EF2_RndHs, /* Size in pixels */
  EF2_RndWp, EF2_RndHp, /* Size of view */
  EF2_RndProjDist;      /* Project distance */

/* Matrix */
extern MATR
  EF2_RndMatrWorld, /* Matrix of global SK */
  EF2_RndMatrView,  /* Matrix of lokal SK */
  EF2_RndMatrProjection; /* Projection matrix */



/* From global coordinate to screen coodinates function */
POINT EF2_RndWorldToScreen( VEC P );

/* Load geometric object function */
BOOL EF2_RndGObjLoad( ef2GOBJ *GObj, CHAR *FileName );

/* Free memory from geometric object function */
VOID EF2_RndGObjFree( ef2GOBJ *GObj );

/* Draw geometric object function */
VOID EF2_RndGObjDraw( ef2GOBJ *GObj, HDC hDC );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
