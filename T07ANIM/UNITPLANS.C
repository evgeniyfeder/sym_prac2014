/* FILENAME: UNITPLANS.C
 * PROGRAMMER: EF2
 * PURPOSE: Plans unit handle module.
 * LAST UPDATE: 17.06.2014
 */

#include <stdlib.h>
#include <string.h>

#include "anim.h"

/* Main type of unit */
typedef struct tagef2UNIT_PLANS
{
  EF2_UNIT_BASE_FIELDS;
  FLT SizeCube;
  UINT TexNoEarth, TexNoSky;
} ef2UNIT_PLANS;

/* Default Init unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT_PLANS *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_PlansUnitInit( ef2UNIT_PLANS *Unit, ef2ANIM *Ani )
{
  IMAGE Img;
  INT i = 0;

  Unit->SizeCube = 100;
  Unit->TexNoEarth = 0;
  Unit->TexNoSky = 0;

  ImageLoad(&Img, "Z:\\SUM2014\\T07ANIM\\Textures\\texture_025.bmp");

  /* получаем свободный номер текстуры */
  glGenTextures(1, &Unit->TexNoEarth);
  /* делаем ее активной */
  glBindTexture(GL_TEXTURE_2D, Unit->TexNoEarth);
  for (i = 0; i < Img.W * Img.H; i++)
    Img.Bits[i] |= 0xFF000000;
  /* отправляем картинку в видеопамять */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Img.W, Img.H,
    GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.Bits);

  /* Параметры вывода */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  ImageFree(&Img);

  ImageLoad(&Img, "Z:\\SUM2014\\T07ANIM\\Textures\\Sky_18.bmp");

  /* получаем свободный номер текстуры */
  glGenTextures(1, &Unit->TexNoSky);
  /* делаем ее активной */
  glBindTexture(GL_TEXTURE_2D, Unit->TexNoSky);
  for (i = 0; i < Img.W * Img.H; i++)
    Img.Bits[i] |= 0xFF000000;
  /* отправляем картинку в видеопамять */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Img.W, Img.H,
    GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.Bits);

  /* Параметры вывода */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  ImageFree(&Img);
} /* End of 'EF2_AnimUnitInit' function */

/* Close unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT_PLANS *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_PlansUnitClose( ef2UNIT_PLANS *Unit, ef2ANIM *Ani )
{
  glDeleteTextures(1, &Unit->TexNoEarth);
  glDeleteTextures(1, &Unit->TexNoSky);
} /* End of 'EF2_AnimUnitClose' function */

/* Response unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT_PLANS *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_PlansUnitResponse( ef2UNIT_PLANS *Unit, ef2ANIM *Ani )
{
} /* End of 'EF2_AnimUnitResponse' function */

/* Render unit of animation function.
 * ARGUMENTS:
 *   - pointer for animation:
 *       ef2UNIT_PLANS *Unit;
 *   - pointer to animation:
 *       ef2ANIM *Ani;
 * RETURNS: None.
 */
static VOID EF2_PlansUnitRender( ef2UNIT_PLANS *Unit, ef2ANIM *Ani )
{
  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Unit->TexNoSky);
  glColor3d(1, 1, 1);
  glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(1, 1);
    glVertex3d(100, 0.1, 100);
    glTexCoord2d(0, 1);
    glVertex3d(-100, 0.1, 100);
    glTexCoord2d(0, 0);
    glVertex3d(-100, 0.1, -100);
    glTexCoord2d(1, 0);
    glVertex3d(100, 0.1, -100);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Unit->TexNoSky);
  glColor3d(1, 1, 1);
  glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(1, 1);
    glVertex3d(-100, 100, -100);
    glTexCoord2d(0, 1);
    glVertex3d(100, 100, -100);
    glTexCoord2d(0, 0);
    glVertex3d(-100, 0, -100);
    glTexCoord2d(1, 0);
    glVertex3d(100, 0, -100);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
} /* End of 'EF2_AnimUnitRender' function */

/* Create unit of animation function.
 * ARGUMENTS:
 *   - size to structure of animation:
 *       INT Size;
 * RETURNS:
 *   (ef2UNIT_PLANS *) pointer to unit.
 */
ef2UNIT * EF2_PlansUnitCreate( VOID )
{
  ef2UNIT_PLANS *Unit;

  if ((Unit = (ef2UNIT_PLANS *)EF2_AnimUnitCreate(sizeof(ef2UNIT_PLANS))) == NULL)
    return NULL;
  /* create default unit */
  Unit->Init = (VOID *)EF2_PlansUnitInit;
  Unit->Close = (VOID *)EF2_PlansUnitClose;
  Unit->Response = (VOID *)EF2_PlansUnitResponse;
  Unit->Render = (VOID *)EF2_PlansUnitRender;
  return (ef2UNIT *)Unit;
} /* End of 'EF2_AnimUnitCreate' function */
