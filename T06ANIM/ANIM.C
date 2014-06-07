/* FILENAME: ANIM.C
 * PROGRAMMER: EF2
 * PURPOSE: Base animation module
 * LAST UPDATE: 07.06.2014
 */

#include <stdlib.h>
#include <time.h>

#include "anim.h"

/* System contecs of animation */
static ef2ANIM EF2_Anim;

/* Data for sinhronize time */
static INT64
  TimeFreq,  /* CLOCKS_PER_SEC */
  TimeStart, /* begin of animation */
  TimeOld,   /* time of old frame */
  TimePause, /* time of pause */
  TimeFPS;   /* time for FPS */
static INT
  FrameCounter; /* counter of frames */

/* Init animation function.
 * ARGUMENTS:
 *   - hWnd of window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EF2_AnimInit( HWND hWnd )
{
  HDC hDC = GetDC(hWnd);
  LARGE_INTEGER li;

  EF2_Anim.hWnd = hWnd;
  EF2_Anim.hDC = CreateCompatibleDC(hDC);
  EF2_Anim.hBmFrame = CreateCompatibleBitmap(hDC, 30, 30);
  EF2_Anim.W = 30;
  EF2_Anim.H = 30;
  EF2_Anim.NumOfUnits = 0;
  ReleaseDC(hWnd, hDC);

  /* init of timer */
  QueryPerformanceFrequency(&li);
  TimeFreq = li.QuadPart;

  QueryPerformanceCounter(&li);
  TimeStart = TimeOld = TimeFPS = li.QuadPart;
  TimePause = 0;
  FrameCounter = 0;
} /* End of 'EF2_AnimInit' function */

/* Uninit animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EF2_AnimClose( VOID )
{
  INT i;

  /* Free memory from unit of animation */
  for (i = 0; i < EF2_Anim.NumOfUnits; i++)
  {
    EF2_Anim.Units[i]->Close(EF2_Anim.Units[i], &EF2_Anim);
    free(EF2_Anim.Units[i]);
  }
  DeleteObject(EF2_Anim.hBmFrame);
  DeleteDC(EF2_Anim.hDC);
  memset(&EF2_Anim, 0, sizeof(ef2ANIM));
} /* End of 'EF2_AnimInit' function */

/* Resize of animation function.
 * ARGUMENTS:
 *   - new width and height of animation:
 *       INT W, H;
 * RETURNS: None.
 */
VOID EF2_AnimResize( INT W, INT H )
{
  HDC hDC = GetDC(EF2_Anim.hWnd);

  /* Remalloc memory */
  DeleteObject(EF2_Anim.hBmFrame);
  EF2_Anim.hBmFrame = CreateCompatibleBitmap(hDC, W, H);
  SelectObject(EF2_Anim.hDC, EF2_Anim.hBmFrame);

  /* Save width and height */
  EF2_Anim.W = W;
  EF2_Anim.H = H;

  ReleaseDC(EF2_Anim.hWnd, hDC);
} /* End of 'EF2_AnimResize' function */

/* Render farme of animation.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EF2_AnimRender( VOID )
{
  INT i;
  LARGE_INTEGER li;

  /* Update keys */
  GetKeyboardState(EF2_Anim.Keys);
  for (i = 0; i < 256; i++)
    EF2_Anim.Keys[i] >>= 7;

  /* Update of time */
  EF2_Anim.Time = (DBL)clock() / CLOCKS_PER_SEC;

  /* Update frame */
  QueryPerformanceCounter(&li);

  /* Global time */
  EF2_Anim.GlobalTime = (DBL)(li.QuadPart - TimeStart) / TimeFreq;
  EF2_Anim.GlobalDeltaTime = (DBL)(li.QuadPart - TimeOld) / TimeFreq;

  /* Local time */
  if (EF2_Anim.IsPause)
  {
    TimePause += li.QuadPart - TimeOld;
    EF2_Anim.DeltaTime = 0;
  }
  else
    EF2_Anim.DeltaTime = EF2_Anim.GlobalDeltaTime;

  EF2_Anim.Time = (DBL)(li.QuadPart - TimeStart - TimePause) / TimeFreq;

  /* count FPS */
  if (li.QuadPart - TimeFPS > TimeFreq)
  {
    EF2_Anim.FPS = FrameCounter / ((DBL)(li.QuadPart - TimeFPS) / TimeFreq);
    TimeFPS = li.QuadPart;
    FrameCounter = 0;
  }

  /* time of old frame */
  TimeOld = li.QuadPart;

  /* clean brush */
  SelectObject(EF2_Anim.hDC, GetStockObject(DC_BRUSH));
  SelectObject(EF2_Anim.hDC, GetStockObject(NULL_PEN));
  SetDCBrushColor(EF2_Anim.hDC, RGB(0, 110, 0));
  Rectangle(EF2_Anim.hDC, 0, 0, EF2_Anim.W, EF2_Anim.H);

  for (i = 0; i < EF2_Anim.NumOfUnits; i++)
    EF2_Anim.Units[i]->Response(EF2_Anim.Units[i], &EF2_Anim);

  /* draw of units */
  for (i = 0; i < EF2_Anim.NumOfUnits; i++)
  {
    SelectObject(EF2_Anim.hDC, GetStockObject(DC_BRUSH));
    SelectObject(EF2_Anim.hDC, GetStockObject(DC_PEN));
    SetDCBrushColor(EF2_Anim.hDC, RGB(0, 0, 0));
    SetDCPenColor(EF2_Anim.hDC, RGB(55, 155, 255));
    EF2_Anim.Units[i]->Render(EF2_Anim.Units[i], &EF2_Anim);
  }

  FrameCounter++;
} /* End of 'EF2_AnimRender' function */

/* Output frame of animation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EF2_AnimCopyFrame( VOID )
{
  HDC hDC;

  /* output of frame */
  hDC = GetDC(EF2_Anim.hWnd);
  BitBlt(hDC, 0, 0, EF2_Anim.W, EF2_Anim.H, EF2_Anim.hDC, 0, 0, SRCCOPY);
  ReleaseDC(EF2_Anim.hWnd, hDC);
} /* End of 'EF2_AnimCopyFrame' function */

/* Add unit to animation function.
 * ARGUMENTS:
 *   - added unit of animation:
 *       ef2UNIT *Unit;
 * RETURNS: None.
 */
VOID EF2_AnimAddUnit( ef2UNIT *Unit )
{
  if (EF2_Anim.NumOfUnits < EF2_MAX_UNITS)
  {
    EF2_Anim.Units[EF2_Anim.NumOfUnits++] = Unit;
    Unit->Init(Unit, &EF2_Anim);
  }
} /* End of 'EF2_AnimAddUnit' function */

/* Do fullscreen in manyscreens function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EF2_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; 
  static RECT SaveRC;               

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* save old orientation of screen */
    GetWindowRect(EF2_Anim.hWnd, &SaveRC);

    hmon = MonitorFromWindow(EF2_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* ger information of screen */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(EF2_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(EF2_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    /* update size of screen */
    SetWindowPos(EF2_Anim.hWnd, HWND_TOPMOST,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'EF2_AnimFlipFullScreen' function */

/* Set pause in animation function.
 * ARGUMENTS:
 *   - flag of pause:
 *       BOOL NewPauseFlag;
 * RETURNS: None.
 */
VOID EF2_AnimSetPause( BOOL NewPauseFlag )
{
  EF2_Anim.IsPause = NewPauseFlag;
} /* End of 'EF2_AnimSetPause' function */


/* END OF 'ANIM.C' FILE */
