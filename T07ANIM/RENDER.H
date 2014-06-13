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

/* Load geometric object function */
BOOL EF2_RndGObjLoad( ef2GOBJ *GObj, CHAR *FileName );

/* Free memory from geometric object function */
VOID EF2_RndGObjFree( ef2GOBJ *GObj );

/* Draw geometric object function */
VOID EF2_RndGObjDraw( ef2GOBJ *GObj, HDC hDC );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
