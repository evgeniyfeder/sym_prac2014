/* FILENAME: SAMPLE.C
 * PROGRAMMER: EF2
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 07.06.2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "anim.h"

/* Structure of cow's unit */
typedef struct tagef2UNIT_COW
{
  EF2_UNIT_BASE_FIELDS; /* Base things of units */
  DBL ShiftX, ShiftY;   /* Shift in x and y */
  INT Type;             /* Type of unit */
} ef2UNIT_COW;

/* Init unit of animation function.
 * ARGUMENTS:
 *   - pointer to unit of animation:
 *       ef2UNIT_COW *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID CowUnitInit( ef2UNIT_COW *Unit, ef2ANIM *Ani )
{
} /* End of 'CowUnitInit' function */

/* Uninit unit of animation function.
 * ARGUMENTS:
 *   - pointer to unit of animation:
 *       ef2UNIT_COW *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID CowUnitClose( ef2UNIT_COW *Unit, ef2ANIM *Ani )
{
} /* End of 'CowUnitClose' function */

/* Response unit of animation function.
 * ARGUMENTS:
 *   - pointer to unit of animation:
 *       ef2UNIT_COW *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID CowUnitResponse( ef2UNIT_COW *Unit, ef2ANIM *Ani )
{
} /* End of 'CowUnitResponse' function */

/* Render unit of animation function.
 * ARGUMENTS:
 *   - pointer to unit of animation:
 *       ef2UNIT_COW *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID CowUnitRender( ef2UNIT_COW *Unit, ef2ANIM *Ani )
{
  DBL
    x = Unit->ShiftX + sin(Ani->Time + Unit->ShiftX) * 30,
    y = Unit->ShiftY + sin(Ani->Time + Unit->ShiftY) * 30;

  if (Unit->Type)
    Rectangle(Ani->hDC, x, y, x + 30, y + 30);
  else
    Ellipse(Ani->hDC, x, y, x + 30, y + 30);
} /* End of 'EF2_AnimUnitRender' function */

/* Create unit of animation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ef2UNIT *) pointer to new unit.
 */
ef2UNIT * EF2_CowUnitCreate( VOID )
{
  ef2UNIT_COW *Unit;

  if ((Unit = (ef2UNIT_COW *)EF2_AnimUnitCreate(sizeof(ef2UNIT_COW))) == NULL)
    return NULL;
  /* create default unit */
  Unit->Init = (VOID *)CowUnitInit;
  Unit->Close = (VOID *)CowUnitClose;
  Unit->Response = (VOID *)CowUnitResponse;
  Unit->Render = (VOID *)CowUnitRender;
  Unit->ShiftX = 30 * 30.59 * rand() / RAND_MAX;
  Unit->ShiftY = 30 * 30.59 * rand() / RAND_MAX;
  Unit->Type = rand() % 2;
  return (ef2UNIT *)Unit;
} /* End of 'EF2_CowUnitCreate' function */

/***********************************************************/

/* Draw arrow function.
 * ARGUMENTS:
 *   - handle of screen:
 *       HDC hDC;
 *   - coordinates of point:
 *       INT Xc, Yc;
 *   - len and weidth:
 *       INT L, W;
 *   - angle
 *       FLOAT Angle;
 * RETURNS: None.
 */
VOID DrawArrow( HDC hDC, INT Xc, INT Yc, INT L, INT W, FLOAT Angle )
{
  INT i;
  POINT pts[] =
  {
    {0, -W}, {-W, 0}, {0, L}, {W, 0}
  }, pts_draw[sizeof pts / sizeof pts[0]];
  FLOAT si = sin(Angle), co = cos(Angle);

  for (i = 0; i < sizeof pts / sizeof pts[0]; i++)
  {
    pts_draw[i].x = Xc + pts[i].x * co - pts[i].y * si;
    pts_draw[i].y = Yc + pts[i].x * si + pts[i].y * co;
  }
  Polygon(hDC, pts_draw, sizeof pts / sizeof pts[0]);
} /* End of 'DrawArrow' function */

/* Output information of animation function.
 * ARGUMENTS:
 *   - pointer to unit of animation:
 *       ef2UNIT_COW *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID InfoUnitRender( ef2UNIT *Unit, ef2ANIM *Ani )
{
  static CHAR Buf[1000];
  static SYSTEMTIME SysTime;

  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(255, 255, 155));
  TextOut(Ani->hDC, 10, 10, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));
  GetSystemTime(&SysTime);
  DrawArrow(Ani->hDC, Ani->W / 2, Ani->H / 2, Ani->W / 4, 100, 3.1415 / 2 - SysTime.wMinute / 60 * 2 * 3.1415926535);
} /* End of 'EF2_AnimUnitRender' function */


/* Create information unit function
 * ARGUMENTS: None.
 * RETURNS:
 *   (ef2UNIT *) Pointer to untio of animation.
 */
ef2UNIT * EF2_InfoUnitCreate( VOID )
{
  ef2UNIT *Unit;

  if ((Unit = EF2_AnimUnitCreate(sizeof(ef2UNIT))) == NULL)
    return NULL;
  /* create default settings */
  Unit->Render = (VOID *)InfoUnitRender;
  return Unit;
} /* End of 'EF2_InfoUnitCreate' function */

/* END OF 'SAMPLE.C' FILE */
