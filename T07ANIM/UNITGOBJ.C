/* FILENAME: UNITGOBJ.C
 * PROGRAMMER: EF2
 * PURPOSE: Animation unit samples handle module.
 * LAST UPDATE: 13.06.2014
 */

#include <string.h>
#include <stdlib.h>

#include "anim.h"
#include "render.h"

/* Unit for geometric object data type */
typedef struct tagef2UNIT_GOBJ
{
  EF2_UNIT_BASE_FIELDS;  /* Base fields of unit */
  ef2GOBJ *Obj;           /* Geometric object */
} ef2UNIT_GOBJ;

ef2CAMERA EF2_RndCam;

/* Init geometric unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_GobjUnitInit( ef2UNIT_GOBJ *Unit, ef2ANIM *Ani )
{
  if ((Unit->Obj = malloc(sizeof(ef2GOBJ))) == NULL)
    return;
  EF2_RndGObjLoad(&Unit->Obj[0], "cow.object");
  //EF2_RndGObjLoad(&Unit->Obj[1], "avent.object");
} /* End of 'EF2_GobjUnitInit' function */

/* Close geometric unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_GobjUnitClose( ef2UNIT_GOBJ *Unit, ef2ANIM *Ani )
{
  EF2_RndGObjFree(Unit->Obj);
} /* End of 'EF2_GobjUnitClose' function */

/* Response geometric unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_GobjUnitResponse( ef2UNIT_GOBJ *Unit, ef2ANIM *Ani )
{
} /* End of 'EF2_GobjUnitResponse' function */

/* Render unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_GobjUnitRender( ef2UNIT_GOBJ *Unit, ef2ANIM *Ani )
{
  static MATR EF2_RndMatrWorldViewProj;
  int i = 0;
  
  EF2_RndMatrWorldViewProj = MatrIdenity();
  Ani->MatrView = EF2_MatrViewLookAt(EF2_MatrMultVec(EF2_MatrRotateX(5 * Ani->CountY), VecSet(10, 10, Ani->CountX + 15)), VecSet(0, 0, 0), VecSet(0, 1, 0));
  //Ani->MatrView = EF2_MatrMult4x4(Ani->MatrView, EF2_MatrRotateY(Ani->Time * 10));
  Ani->MatrWorld = EF2_MatrRotateY(Ani->Time * 20);
  Ani->MatrWorld = EF2_MatrMult4x4(MatrScale(0.30, 0.30, 0.30), Ani->MatrWorld);
  //Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0.0, 0.0, 3 * 3.30), Ani->MatrWorld);
  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixd(&EF2_RndMatrWorldViewProj.A[0][0]);
  EF2_RndGObjDraw(&Unit->Obj[0], Ani->hDC);

  
  Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0, 0, 10), Ani->MatrWorld);
  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixd(&EF2_RndMatrWorldViewProj.A[0][0]);
  EF2_RndGObjDraw(&Unit->Obj[0], Ani->hDC);
  
  Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0, 0, -10), Ani->MatrWorld);

  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixd(&EF2_RndMatrWorldViewProj.A[0][0]);
} /* End of 'EF2_GobjUnitRender' function */

/* Create geometric unit of animation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ef2UNIT *) pointer to new unit.
 */
ef2UNIT * EF2_GobjUnitCreate( VOID )
{
  ef2UNIT_GOBJ *Unit;

  if ((Unit = (ef2UNIT_GOBJ *)EF2_AnimUnitCreate(sizeof(ef2UNIT_GOBJ))) == NULL)
    return NULL;
  /* create default unit */
  Unit->Init = (VOID *)EF2_GobjUnitInit;
  Unit->Close = (VOID *)EF2_GobjUnitClose;
  Unit->Response = (VOID *)EF2_GobjUnitResponse;
  Unit->Render = (VOID *)EF2_GobjUnitRender;
  return (ef2UNIT *)Unit;
} /* End of 'EF2_GobjUnitCreate' function */

/* END OF 'UNITGOBJ.C' FILE */
