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
  EF2_UNIT_BASE_FIELDS;   /* Base fields of unit */
  ef2GEOM *Obj;           /* Geometric object */
  UINT TexNo1;            /* Texture numver of texture */
} ef2UNIT_GOBJ;

ef2CAMERA EF2_RndCam;
static UINT TexNo1, TexNo2;

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
  ef2PRIM Pr[6] = {0};
  ef2MATERIAL Mtl[2] = {0};
  UINT TexNo = 0;
  if ((Unit->Obj = malloc(sizeof(ef2GEOM))) == NULL)
    return;
  memset(&Unit->Obj[0], 0, sizeof(ef2GEOM));
  //EF2_GeomLoad(&Unit->Obj[0], "Z:\\SUM2014\\T07ANIM\\x6\\x6.object");
  //EF2_RndGObjLoad(&Unit->Obj[1], "avent.object");
  //EF2_GeomLoad(&Unit->Obj[0], "Z:\\SUM2014\\T07ANIM\\houses\\house1.object");
  //EF2_GeomLoad(&Unit->Box, "Z:\\SUM2014\\T07ANIM\\Models\\Cube\\cube.object");
  EF2_PrimCreatePlane(&Pr[0], VecSet(-100, 0, -100), VecSet(100, 0, -100), VecSet(-100, 0, 100), VecSet(100, 0, 100), VecSet(0, 1, 0), 20);

  /* Create material for planes */
  Mtl[0].Trans = 1;
  Mtl[0].Phong = 30;
  Mtl[0].Ka = VecSet(0.1, 0.1, 0.1);
  Mtl[0].Kd = VecSet(1, 1, 1);
  Mtl[0].Ks = VecSet(0, 0, 0);
  strcpy(Mtl[0].MapD, "Z:\\SUM2014\\T07ANIM\\Textures\\e1.bmp");
  strcpy(Mtl[0].Name, "Plane Field Material");
  TexNo1 = Pr[0].Mtl = EF2_GeomAddMaterial(&Unit->Obj[0], &Mtl[0]);
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[0]);

  
  Mtl[1].Trans = 1;
  Mtl[1].Phong = 30;
  Mtl[1].Ka = VecSet(0.1, 0.1, 0.1);
  Mtl[1].Kd = VecSet(1, 1, 1);
  Mtl[1].Ks = VecSet(0, 0, 0);
  strcpy(Mtl[1].MapD, "Z:\\SUM2014\\T07ANIM\\Textures\\s1.bmp");
  strcpy(Mtl[1].Name, "Sky Field Material");
  TexNo2 = EF2_GeomAddMaterial(&Unit->Obj[0], &Mtl[1]);  
  
  /* Create planes */
  EF2_PrimCreatePlane(&Pr[1], VecSet(-100, 0, -100), VecSet(100, 0, -100), VecSet(-100, 100, -100), VecSet(100, 100, -100), VecSet(0, 0, 1), 5);
  Pr[1].Mtl = TexNo2;
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[1]);
  
  EF2_PrimCreatePlane(&Pr[2], VecSet(-100, 0, -100), VecSet(-100, 0, 100), VecSet(-100, 100, -100), VecSet(-100, 100, 100), VecSet(1, 0, 0), 5);
  Pr[2].Mtl = TexNo2;
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[2]);

  EF2_PrimCreatePlane(&Pr[3], VecSet(-100, 0, 100), VecSet(100, 0, 100), VecSet(-100, 100, 100), VecSet(100, 100, 100), VecSet(0, 0, -1), 5);
  Pr[3].Mtl = TexNo2;
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[3]);

  EF2_PrimCreatePlane(&Pr[4], VecSet(100, 0, -100), VecSet(100, 0, 100), VecSet(100, 100, -100), VecSet(100, 100, 100), VecSet(-1, 0, 0), 5);
  Pr[4].Mtl = TexNo2;
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[4]);

  EF2_PrimCreatePlane(&Pr[5], VecSet(-100, 100, -100), VecSet(100, 100, -100), VecSet(-100, 100, 100), VecSet(100, 100, 100), VecSet(0, -1, 0), 5);
  Pr[5].Mtl = TexNo2;
  EF2_GeomAddPrim(&Unit->Obj[0], &Pr[5]);

  /* Init camera */
  EF2_RndCam.At = VecSet(0, 0, 0);
  EF2_RndCam.Loc = VecSet(5, 5, 5);
  EF2_RndCam.Up = VecSet(0, 1, 0);
  EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
  EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);
} /* End of 'EF2_GobjUnitInit' function */

/* Get matrix for camera function */
MATR EF2_MatrCameraGetMatrix( VOID )
{
  MATR RetMatr = 
  {
    {
      { EF2_RndCam.Dir.X  , EF2_RndCam.Dir.Y  , EF2_RndCam.Dir.Z  , 0 },
      { EF2_RndCam.Up.X   , EF2_RndCam.Up.Y   , EF2_RndCam.Up.Z   , 0 },
      { EF2_RndCam.Right.X, EF2_RndCam.Right.Y, EF2_RndCam.Right.Z, 0 },
      {                  0,                  0,                 0 , 1 }
    }
  };
  return RetMatr;
} /* End of 'EF2_MatrCameraGetMatrix' funciton */

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
  glDeleteTextures(1, &TexNo1);
  glDeleteTextures(1, &TexNo2);
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
  MATR M;

  if (Ani->Keys['W'])
  {
    EF2_RndCam.Loc = VecAddVec(EF2_RndCam.Loc, VecMulNum(EF2_RndCam.Dir, 0.1));
    EF2_RndCam.At = VecAddVec(EF2_RndCam.At, VecMulNum(EF2_RndCam.Dir, 0.1));
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, EF2_RndCam.At, EF2_RndCam.Up);
  }
  if (Ani->Keys['S'])
  {
    EF2_RndCam.Loc = VecSubVec(EF2_RndCam.Loc, VecMulNum(EF2_RndCam.Dir, 0.1));
    EF2_RndCam.At = VecSubVec(EF2_RndCam.At, VecMulNum(EF2_RndCam.Dir, 0.1));
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, EF2_RndCam.At, EF2_RndCam.Up);
  }
  if (Ani->Keys['D'])
  {
    EF2_RndCam.Loc = VecAddVec(EF2_RndCam.Loc, VecMulNum(EF2_RndCam.Right, 0.1));
    EF2_RndCam.At = VecAddVec(EF2_RndCam.At, VecMulNum(EF2_RndCam.Right, 0.1));
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, EF2_RndCam.At, EF2_RndCam.Up);
  }
  if (Ani->Keys['A'])
  {
    EF2_RndCam.Loc = VecSubVec(EF2_RndCam.Loc, VecMulNum(EF2_RndCam.Right, 0.1));
    EF2_RndCam.At = VecSubVec(EF2_RndCam.At, VecMulNum(EF2_RndCam.Right, 0.1));
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, EF2_RndCam.At, EF2_RndCam.Up);
  }
  if (Ani->Keys[VK_NUMPAD8])
  {    
    /* EF2_RndCam.Loc = VecNormalize(EF2_RndCam.Loc); */
    EF2_RndCam.At = VecNormalize(EF2_RndCam.At);
    EF2_RndCam.Dir = VecNormalize(EF2_RndCam.Dir);
    EF2_RndCam.Right = VecNormalize(EF2_RndCam.Right);
    EF2_RndCam.Up = VecNormalize(EF2_RndCam.Up);
    
    M = EF2_MatrCameraGetMatrix();
    M = EF2_MatrMult4x4(EF2_MatrRotateZ(1), M);
    EF2_RndCam.At = VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2]));
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2])), EF2_RndCam.Up);
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);    
  }
  if (Ani->Keys[VK_NUMPAD2])
  {    
    /* EF2_RndCam.Loc = VecNormalize(EF2_RndCam.Loc); */
    EF2_RndCam.At = VecNormalize(EF2_RndCam.At);
    EF2_RndCam.Dir = VecNormalize(EF2_RndCam.Dir);
    EF2_RndCam.Right = VecNormalize(EF2_RndCam.Right);
    EF2_RndCam.Up = VecNormalize(EF2_RndCam.Up);
    
    M = EF2_MatrCameraGetMatrix();
    M = EF2_MatrMult4x4(EF2_MatrRotateZ(-1), M);
    EF2_RndCam.At = VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2]));
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2])), EF2_RndCam.Up);
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);    
  }
  if (Ani->Keys[VK_NUMPAD6])
  {    
    /* EF2_RndCam.Loc = VecNormalize(EF2_RndCam.Loc); */
    EF2_RndCam.At = VecNormalize(EF2_RndCam.At);
    EF2_RndCam.Dir = VecNormalize(EF2_RndCam.Dir);
    EF2_RndCam.Right = VecNormalize(EF2_RndCam.Right);
    EF2_RndCam.Up = VecNormalize(EF2_RndCam.Up);
    
    M = EF2_MatrCameraGetMatrix();
    M = EF2_MatrMult4x4(EF2_MatrRotateY(-1), M);
    EF2_RndCam.At = VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2]));
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2])), EF2_RndCam.Up);
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);    
  }
  if (Ani->Keys[VK_NUMPAD4])
  {    
    /* EF2_RndCam.Loc = VecNormalize(EF2_RndCam.Loc); */
    EF2_RndCam.At = VecNormalize(EF2_RndCam.At);
    EF2_RndCam.Dir = VecNormalize(EF2_RndCam.Dir);
    EF2_RndCam.Right = VecNormalize(EF2_RndCam.Right);
    EF2_RndCam.Up = VecNormalize(EF2_RndCam.Up);
    
    M = EF2_MatrCameraGetMatrix();
    M = EF2_MatrMult4x4(EF2_MatrRotateY(1), M);
    EF2_RndCam.At = VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2]));
    Ani->MatrView = EF2_MatrViewLookAt(EF2_RndCam.Loc, VecAddVec(EF2_RndCam.Loc, VecSet(M.A[0][0], M.A[0][1], M.A[0][2])), EF2_RndCam.Up);
    EF2_RndCam.Dir = VecSubVec(EF2_RndCam.At, EF2_RndCam.Loc);
    EF2_RndCam.Right = VecCrossVec(EF2_RndCam.Dir, EF2_RndCam.Up);    
  }
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
  //Ani->MatrWorld = EF2_MatrMult4x4(MatrTranslate(0, -1, 0), MatrIdenity());
  /*Ani->MatrView =
    EF2_MatrViewLookAt(
    EF2_MatrMultVec(EF2_MatrRotateY(Ani->JR * 90), EF2_MatrMultVec(EF2_MatrRotateZ(Ani->JY * 90 + 1), Ani->PosCam)),
      VecSet(0, 0, 0), VecSet(0, 1, 0));*/
  WVP = EF2_MatrMult4x4(EF2_Anim.MatrWorld, EF2_MatrMult4x4(EF2_Anim.MatrView, EF2_Anim.MatrProjection));
  glLoadMatrixf(WVP.A[0]);

  glLineWidth(3);
  

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

  Ani->MatrWorld = EF2_MatrRotateY(Ani->PosCam.X * 10);
  Ani->MatrWorld = EF2_MatrMult4x4(EF2_MatrRotateX(0), Ani->MatrWorld);
  glEnable(GL_DEPTH_TEST);
  EF2_GeomDraw(&Unit->Obj[0]);
  //EF2_GeomDraw(&Unit->Obj[1]);
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
