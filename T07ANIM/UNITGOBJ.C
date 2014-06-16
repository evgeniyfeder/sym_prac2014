/* FILENAME: UNITGOBJ.C
 * PROGRAMMER: EF2
 * PURPOSE: Animation unit samples handle module.
 * LAST UPDATE: 13.06.2014
 */

#include <string.h>
#include <stdlib.h>

#include "anim.h"
#pragma warning(disable: 4244 4305)

/* Unit for geometric object data type */
typedef struct tagef2UNIT_GOBJ
{
  EF2_UNIT_BASE_FIELDS;  /* Base fields of unit */
  ef2GEOM *Obj;           /* Geometric object */
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
  if ((Unit->Obj = malloc(sizeof(ef2GEOM))) == NULL)
    return;
  //EF2_GeomLoad(&Unit->Obj[0], "Z:\\SUM2014\\T07ANIM\\x6\\x6.object");
  //EF2_RndGObjLoad(&Unit->Obj[1], "avent.object");
  EF2_GeomLoad(&Unit->Obj[0], "Z:\\SUM2014\\T07ANIM\\houses\\house1.object");
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
  EF2_GeomFree(&Unit->Obj[0]);
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
  /*
  static MATR EF2_RndMatrWorldViewProj;
  INT i = 0, loc = 0;
  static DBL time = 0;
  
  EF2_RndMatrWorldViewProj = MatrIdenity();
  Ani->MatrView = EF2_MatrViewLookAt(EF2_MatrMultVec(EF2_MatrRotateX(5 * Ani->CountY), VecSet(10, 10, Ani->CountX + 15)), VecSet(0, 0, 0), VecSet(0, 1, 0));
  //Ani->MatrView = EF2_MatrMult4x4(Ani->MatrView, EF2_MatrRotateY(Ani->Time * 10));
  Ani->MatrWorld = EF2_MatrRotateY(Ani->Time * 20);
  Ani->MatrWorld = EF2_MatrMult4x4(MatrScale(0.30, 0.30, 0.30), Ani->MatrWorld);
  //Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0.0, 0.0, 3 * 3.30), Ani->MatrWorld);
  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixf(&EF2_RndMatrWorldViewProj.A[0][0]);

  time += Ani->GlobalDeltaTime;
  if (time > 1)
  {
    time = 0;
    EF2_ShadProgClose(EF2_ShaderProg);
    EF2_ShaderProg = EF2_ShadProgInit("a.vert", "a.frag");
  }
 
  /* выбор программы шейдеров вывода примитивов 
  glEnable(GL_DEPTH_TEST);
  glUseProgram(EF2_ShaderProg);
  loc = glGetUniformLocation(EF2_ShaderProg, "Matr");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, EF2_RndMatrWorldViewProj.A[0]);
  loc = glGetUniformLocation(EF2_ShaderProg, "Time");
  if (loc != -1)
    glUniform1f(loc, Ani->Time);

  EF2_RndGObjDraw(&Unit->Obj[0], Ani->hDC);

  /*
  Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0, 0, 10), Ani->MatrWorld);
  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixf(&EF2_RndMatrWorldViewProj.A[0][0]);
  EF2_RndGObjDraw(&Unit->Obj[0], Ani->hDC);
  
  //Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0, 10 * sin(Ani->Time), -10), Ani->MatrWorld);

  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(Ani->MatrWorld, Ani->MatrView),
      Ani->MatrProjection);
  glLoadMatrixf(&EF2_RndMatrWorldViewProj.A[0][0]);
  glUseProgram(0);
  */

  MATR WVP;
  static DBL time;

  /* оси и позиция наблюдателя */
  Ani->MatrWorld = MatrIdenity();
  Ani->MatrView =
    EF2_MatrViewLookAt(
    EF2_MatrMultVec(EF2_MatrRotateY(Ani->JR * 90), EF2_MatrMultVec(EF2_MatrRotateZ(Ani->JY * 90), Ani->PosCam)),
      VecSet(0, 0, 0), VecSet(0, 1, 0));
  WVP = EF2_MatrMult4x4(EF2_Anim.MatrWorld, EF2_MatrMult4x4(EF2_Anim.MatrView, EF2_Anim.MatrProjection));
  glLoadMatrixf(WVP.A[0]);

  glLineWidth(3);
  /*
  glBegin(GL_LINES);
    glColor3d(1, 0.5, 0.5);
    glVertex3d(-3, 0, 0);
    glVertex4d(1, 0, 0, 0);
    glColor3d(0.5, 1, 0.5);
    glVertex3d(0, -3, 0);
    glVertex4d(0, 1, 0, 0);
    glColor3d(0.5, 0.5, 1);
    glVertex3d(0, 0, -3);
    glVertex4d(0, 0, 1, 0);
  glEnd();
  glColorMask(1, 1, 1, 0);
  for (i = -3; i < 30; i++)
  {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(-0.1, -0.1, i);
    glVertex3d(-0.1,  0.1, i);
    glVertex3d( 0.1, -0.1, i);
    glVertex3d( 0.1,  0.1, i);
    glEnd();
  }
  */
  /* Рисуем примитивы */
  time += Ani->GlobalDeltaTime;
  if (time > 1)
  {
    time = 0;
    EF2_ShadProgClose(EF2_ShaderProg);
    EF2_ShaderProg = EF2_ShadProgInit("a.vert", "a.frag");
  }


  glLineWidth(1);
  if (Ani->Keys['Q'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  Ani->MatrWorld = EF2_MatrRotateY(Ani->Time * 30);
  Ani->MatrWorld = EF2_MatrMult4x4(EF2_MatrRotateX(-90), Ani->MatrWorld);
  glEnable(GL_DEPTH_TEST);
  EF2_GeomDraw(&Unit->Obj[0]);
  glUseProgram(0);
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
