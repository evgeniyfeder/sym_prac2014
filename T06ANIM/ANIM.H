/* FILENAME: ANIM.H
 * PROGRAMMER: EF2
 * PURPOSE: Globe project declaration module.
 * LAST UPDATE: 07.06.2014
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "image.h"

/* maximum of units in animation */
#define EF2_MAX_UNITS 3000

/* Declaration of unit */
typedef struct tagef2UNIT ef2UNIT;

/* Structure for animation */
typedef struct tagef2ANIM
{
  HWND hWnd;          /* Output screen */
  INT W, H;           /* Size of screen */
  HBITMAP hBmFrame;   /* Frame of screen */
  HDC hDC;            /* hDC */

  /* Arrey of units in animation */
  ef2UNIT *Units[EF2_MAX_UNITS]; 
  INT NumOfUnits;

  /* Data for sinchronize */
  DBL
    Time,            /* time in seconds from begin */
    GlobalTime,      /* time without pause */
    DeltaTime,       /* time between frames */
    GlobalDeltaTime, /* time between frames without pause */
    FPS;             /* Frames per second */
  BOOL
    IsPause;         /* flag in pause */

  BYTE Keys[256];     /* Key from keybord ot mouse */
} ef2ANIM;

/* Base fields of unit:
 * - size of unit
 *     INT Size;
 * - pointer for init
 *     VOID (*Init)( ef2UNIT *Unit, ef2ANIM *Ani );
 * - pointer for uninit
 *     VOID (*Close)( ef2UNIT *Unit, ef2ANIM *Ani );
 * - pointer for response
 *     VOID (*Response)( ef2UNIT *Unit, ef2ANIM *Ani );
 * - pointer for render
 *     VOID (*Render)( ef2UNIT *Unit, ef2ANIM *Ani );
 */
#define EF2_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( ef2UNIT *Unit, ef2ANIM *Ani );       \
  VOID (*Close)( ef2UNIT *Unit, ef2ANIM *Ani );      \
  VOID (*Response)( ef2UNIT *Unit, ef2ANIM *Ani );   \
  VOID (*Render)( ef2UNIT *Unit, ef2ANIM *Ani )

/* Main type of unit */
struct tagef2UNIT
{
  EF2_UNIT_BASE_FIELDS; /* Base fields */
};

/***
 * Work with animation module of function
 ***/

/* Init of animation function */
VOID EF2_AnimInit( HWND hWnd );

/* Uninit of animation function */
VOID EF2_AnimClose( VOID );

/* Resize of animation function */
VOID EF2_AnimResize( INT W, INT H );

/* Render of animation function */
VOID EF2_AnimRender( VOID );

/* Output anumation function */
VOID EF2_AnimCopyFrame( VOID );

/* do fullscreen to animation function */
VOID EF2_AnimFlipFullScreen( VOID );

/* Set pause in animation function */
VOID EF2_AnimSetPause( BOOL NewPauseFlag );

/***
 * Функции обработки объектов анимации
 ***/

/* Add unit to animation function */
VOID EF2_AnimAddUnit( ef2UNIT *Unit );

/* Create unit function */
ef2UNIT * EF2_AnimUnitCreate( INT Size );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
