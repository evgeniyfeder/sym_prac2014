/* FILENAME: CUBE.C
 * PROGRAMMER: EF2
 * PURPOSE: Animation unit samples handle module.
 * LAST UPDATE: 10.06.2014
 */

#include <string.h>
#include <stdlib.h>

#include "anim.h"
#include "render.h"

/* Unit for geometric object data type */
typedef struct tagef2UNIT_GOBJ
{
  EF2_UNIT_BASE_FIELDS;  /* Base fields of unit */
  ef2GOBJ Obj;           /* Geometric object */
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
  EF2_RndGObjLoad(&Unit->Obj, "cow.object");
  EF2_RndMatrProjection = MatrProjection(-EF2_RndWp / 2, EF2_RndWp / 2, -EF2_RndHp / 2, EF2_RndHp / 2, EF2_RndProjDist, 1000);
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
  EF2_RndGObjFree(&Unit->Obj);
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
  EF2_RndWs = Ani->W;
  EF2_RndHs = Ani->H;
  GetKeyboardState(Ani->Keys);
  if (Ani->Keys['W'] & 0x80)
    EF2_RndCam.At.Y += 1;
  else if (Ani->Keys['S'] & 0x80)
    EF2_RndCam.At.Y -= 1;
  else if (Ani->Keys['A'] & 0x80)
    EF2_RndCam.At.X -= 1;
  else if (Ani->Keys['D'] & 0x80)
    EF2_RndCam.At.X += 1;
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
  /*
  VEC CubeP[] = 
  {
    {0, 0, 0},   
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 1, 1}
  };
  INT F1[][3] =
  {
    {0, 1, 2},
    {2, 3, 0},
    {0, 4, 1},
    {1, 4, 5},
    {1, 2, 6},
    {1, 5, 6},
    {2, 3, 7},
    {2, 6, 7},
    {3, 7, 4},
    {3, 0 ,4},
    {4, 6, 5},
    {4, 5, 6}
  };
  ef2GOBJ Obj;
  Obj.V = CubeP;
  Obj.F = F1;
  Obj.NumOfF = 12;
  Obj.NumOfV = 8;
  */
  EF2_RndMatrView = EF2_MatrViewLookAt(EF2_RndCam.At, VecSet(0, 0, 0), VecSet(0, 1, 0));
  //EF2_RndMatrView = EF2_MatrMult4x4(EF2_RndMatrView, EF2_MatrRotateY(Ani->Time * 10));
  EF2_RndMatrWorld = EF2_MatrRotateY(Ani->Time * 20);
  EF2_RndMatrWorld = EF2_MatrMult4x4(MatrScale(0.10, 0.10, 0.10), EF2_RndMatrWorld);
  //EF2_RndMatrWorld = EF2_MatrMult4x4(MatrTranslate(0.0, 0.0, 3 * 3.30), EF2_RndMatrWorld);
  EF2_RndGObjDraw(&Unit->Obj, Ani->hDC);

  EF2_RndMatrWorld = EF2_MatrRotateY(Ani->Time * 20);
  EF2_RndMatrWorld = EF2_MatrMult4x4(MatrScale(0.10, 0.10, 0.10), EF2_RndMatrWorld);
  EF2_RndMatrWorld = EF2_MatrMult4x4(MatrTranslate(0, 0, 10), EF2_RndMatrWorld);
  EF2_RndGObjDraw(&Unit->Obj, Ani->hDC);
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

/* END OF 'CUBE.C' FILE */
