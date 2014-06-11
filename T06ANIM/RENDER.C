/* FILENAME: RENDER.C
 * PROGRAMMER: EF2
 * PURPOSE: 3D render handle module.
 * LAST UPDATE: 10.06.2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "render.h"

/* Глобальная камера */
ef2CAMERA EF2_RndCam;

/* Параметры проецирования */
DBL
  EF2_RndWs = 30, EF2_RndHs = 30,   /* размеры кадра в точках */
  EF2_RndWp = 4, EF2_RndHp = 3,     /* размеры обрасти проецирования */
  EF2_RndProjDist = 5;              /* расстояние до плоскости проекции */

/* Матрицы */
MATR
  EF2_RndMatrWorld =  /* матрица преобразования мировой СК */
  {                        
    {                      
      {1, 0, 0, 0},        
      {0, 1, 0, 0},        
      {0, 0, 1, 0},        
      {0, 0, 0, 1},        
    }                      
  },
  EF2_RndMatrView = 
  {                        
    {                      
      {1, 0, 0, 0},        
      {0, 1, 0, 0},        
      {0, 0, 1, 0},        
      {0, 0, 0, 1},        
    }                      
  },
  EF2_RndMatrProjection = 
  {                        
    {                      
      {1, 0, 0, 0},        
      {0, 1, 0, 0},        
      {0, 0, 1, 0},        
      {0, 0, 0, 1},        
    }                      
  };
static MATR
  EF2_RndMatrWorldViewProj;              /* Final matrix */


/* Get final matrix function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EF2_RndMatrSetup( VOID )
{
  EF2_RndMatrWorldViewProj =
    EF2_MatrMult4x4(EF2_MatrMult4x4(EF2_RndMatrWorld, EF2_RndMatrView),
      EF2_RndMatrProjection);

} /* End of 'EF2_RndMatrSetup' function */

/* Функция преобразования из мировой системы коорлинат в кадр.
 * АРГУМЕНТЫ:
 *   - исходная точка:
 *       VEC P;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (POINT) координаты в кадре.
 */
POINT EF2_RndWorldToScreen( VEC P )
{
  POINT Ps;
  VEC Pp;

  /* преобразование СК */
  Pp = EF2_MatrMultVec(EF2_RndMatrWorldViewProj, P);
  
  /* проецирование */
  Pp.X *= EF2_RndProjDist / Pp.Z;
  Pp.Y *= EF2_RndProjDist / Pp.Z;

  Ps.x = (Pp.X + EF2_RndWp / 2) / EF2_RndWp * (EF2_RndWs - 1);
  Ps.y = (-Pp.Y + EF2_RndHp / 2) / EF2_RndHp * (EF2_RndHs - 1);

  return Ps;
} /* End of 'EF2_RndWorldToScreen' function */

/* Функция загрузки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на структуру для загружаемой геометрии:
 *       ef2GOBJ *GObj;
 *   - имя файла (*.OBJ):
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе.
 */
BOOL EF2_RndGObjLoad( ef2GOBJ *GObj, CHAR *FileName )
{
  INT nv = 0, nf = 0;
  FILE *F;
  static CHAR Buf[1000];

  /* обнулили данные */
  memset(GObj, 0, sizeof(ef2GOBJ));
  if ((F = fopen(FileName, "r")) == NULL)
    return 0;

  /* считаем количество вершин и граней */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;
  }

  /* выделяем память под вершины и грани как единый участок памяти
   * (memory bulk) */
  GObj->V = malloc(nv * sizeof(VEC) + nf * sizeof(INT [3]));
  GObj->F = (INT (*)[3])(GObj->V + nv);
  GObj->NumOfV = nv;
  GObj->NumOfF = nf;

  /* считываем данные */
  nv = 0;
  nf = 0;
  rewind(F);
  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    DBL x, y, z;
    INT a, b, c;

    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      GObj->V[nv++] = VecSet(x, y, z + 6);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      if (sscanf(Buf + 2, "%i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i//%*i %i//%*i %i//%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i/%*i %i/%*i %i/%*i", &a, &b, &c) == 3 ||
        sscanf(Buf + 2, "%i %i %i", &a, &b, &c))
      {
        GObj->F[nf][0] = a - 1;
        GObj->F[nf][1] = b - 1;
        GObj->F[nf][2] = c - 1;
        nf++;
      }
    }
  }
  fclose(F);
  return TRUE;
} /* End of 'EF2_RndGObjLoad' function */

/* Функция освобождения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на структуру для загружаемой геометрии:
 *       ef2GOBJ *GObj;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID EF2_RndGObjFree( ef2GOBJ *GObj )
{
  if (GObj->V != NULL)
    free(GObj->V);
  memset(GObj, 0, sizeof(ef2GOBJ));
} /* End of 'EF2_RndGObjFree' function */

/* Функция отрисовки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на структуру для загружаемой геометрии:
 *       ef2GOBJ *GObj;
 *   - контекст устройства вывода:
 *       HDC hDC;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID EF2_RndGObjDraw( ef2GOBJ *GObj, HDC hDC )
{
  INT i, s = 1;
  POINT *pts;

  if ((pts = malloc(sizeof(POINT) * GObj->NumOfV)) == NULL)
    return;

  EF2_RndMatrSetup();
  for (i = 0; i < GObj->NumOfV; i++)
    pts[i] = EF2_RndWorldToScreen(GObj->V[i]);
 
  for (i = 0; i < GObj->NumOfF; i++)
  {
    INT
      n0 = GObj->F[i][0],
      n1 = GObj->F[i][1],
      n2 = GObj->F[i][2];
    
      MoveToEx(hDC, pts[n0].x, pts[n0].y, NULL);
      LineTo(hDC, pts[n1].x, pts[n1].y);
      LineTo(hDC, pts[n2].x, pts[n2].y);
      LineTo(hDC, pts[n0].x, pts[n0].y);
  }
  free(pts);
} /* End of 'EF2_RndGObjDraw' function */

/* END OF 'RENDER.C' FILE */
