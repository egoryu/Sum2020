/* FILE NAME: ANIM.C
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "anim.h"

/* Global animation context */
en5ANIM EN5_Anim;

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID EN5_AnimResize( INT W, INT H )
{
  EN5_Anim.H = H;
  EN5_Anim.W = W;
  EN5_RndResize(W, H);
} /* End of 'EN5_AnimResize' function */

/* Copy frame function.
 * ARGUMENTS:
 *   - window context:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID EN5_AnimCopyFrame( HDC hDC )
{
  EN5_RndCopyFrame(hDC);
  EN5_Anim.hDC = hDC;
} /* End of 'EN5_AnimCopyFrame' function */

/* Add unit function.
 * ARGUMENTS:
 *   - unit:
 *       en5UNIT *Uni.
 * RETURNS: None.
 */
VOID EN5_AnimUnitAdd( en5UNIT *Uni )
{
  if (EN5_Anim.NumOfUnits < EN5_MAX_UNITS)
    EN5_Anim.Units[EN5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &EN5_Anim);
} /* End of 'EN5_AnimUnitAdd' function */

/* Initilizate animation function.
 * ARGUMENTS:
 *   - window handel:
 *       HWND hWnd.
 * RETURNS: None.
 */
VOID EN5_AnimInit( HWND hWnd )
{
  EN5_RndInit(hWnd);
  EN5_TimerInit();

  EN5_Anim.hWnd = hWnd;
  EN5_Anim.hDC = EN5_hRndDCFrame;
  EN5_Anim.H = EN5_RndFrameH;
  EN5_Anim.W = EN5_RndFrameW;
} /* End of 'EN5_RndInit' function */

/* Animation system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < EN5_Anim.NumOfUnits; i++)
  {
    EN5_Anim.Units[i]->Close(EN5_Anim.Units[i], &EN5_Anim);
    free(EN5_Anim.Units[i]);
  }
  EN5_Anim.NumOfUnits = 0;
  EN5_RndClose();
} /* End of 'EN5_AnimClose' function */

/* Animation system render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_AnimRender( VOID )
{
  INT i;

  EN5_TimerResponse();
  EN5_AnimKeyboardResponse();
  EN5_AnimMouseResponse();

  for (i = 0; i < EN5_Anim.NumOfUnits; i++)
    EN5_Anim.Units[i]->Response(EN5_Anim.Units[i], &EN5_Anim);

  EN5_RndStart();
  for (i = 0; i < EN5_Anim.NumOfUnits; i++)
    EN5_Anim.Units[i]->Render(EN5_Anim.Units[i], &EN5_Anim);
  EN5_RndEnd();
} /* End of 'EN5_AnimRender' function */

/* Turn full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  IsFullScreen = !IsFullScreen;
  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    /* Goto fullscreen mode */
    GetWindowRect(EN5_Anim.hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(EN5_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(EN5_Anim.hWnd, GWL_STYLE), FALSE);
    SetWindowPos(EN5_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore window size and position */
    SetWindowPos(EN5_Anim.hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
} /* End of 'FlipFullScreen' function */

/* END OF 'ANIM.C' FILE */