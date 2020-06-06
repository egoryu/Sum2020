/* FILE NAME: RNDBASE.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system render handle function
 */

#include "rnd.h"

/* Render systen initialization function.
 * ARGUMENTS:
 *   - HWND:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_RndInit( HWND hWnd )
{
  HDC hDC;

  EN5_hRndWnd = hWnd;

  /* Create fram buffer */
  hDC = GetDC(hWnd);
  EN5_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
  EN5_hRndBmFrame = NULL;

  /* default parametrs */
  EN5_RndFrameH = 102;
  EN5_RndFrameW = 102;

  EN5_RndProjSize = EN5_RndProjDist = 1.0;
  EN5_RndProjFarClip = 300;

  EN5_RndProjSet();
  EN5_RndCamSet(VecSet(4, 4, 4), VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'EN5_RndInit' function */

/* Render systen initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndClose( VOID )
{
  if (EN5_hRndBmFrame != NULL)
    DeleteObject(EN5_hRndBmFrame);
  DeleteDC(EN5_hRndDCFrame);
} /* End of 'EN5_RndClose' function */

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID EN5_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(EN5_hRndWnd);

  if (EN5_hRndBmFrame)
    DeleteObject(EN5_hRndBmFrame);
  EN5_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(EN5_hRndWnd, hDC);
  SelectObject(EN5_hRndDCFrame, EN5_hRndBmFrame);

  /* save size */
  EN5_RndFrameW = W;
  EN5_RndFrameH = H;

  /* recalculat project */
  EN5_RndProjSet();
} /* End of 'EN5_RndResize' function */

/* Change window size function.
 * ARGUMENTS:
 *   - window:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID EN5_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, EN5_RndFrameW, EN5_RndFrameH, EN5_hRndDCFrame, 0, 0, SRCCOPY);
} /* End of 'EN5_RndCopyFrame' function */

/* Start draw function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndStart( VOID )
{
  SelectObject(EN5_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(EN5_hRndDCFrame, GetStockObject(WHITE_BRUSH));
  //SetDCBrushColor(EN5_hRndDCFrame, RGB(20, 100, 50));
  Rectangle(EN5_hRndDCFrame, 0, 0, EN5_RndFrameW + 1, EN5_RndFrameH + 1);
} /* End of 'EN5_RndStart' function */

/* End draw function 
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID EN5_RndEnd( VOID )
{
} /* End of 'EN5_RndEnd' function */

/* Create camera function.
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID EN5_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = EN5_RndProjSize / 2;

  /* Correct aspect ratio */
  if (EN5_RndFrameW > EN5_RndFrameH)
    rx *= (DBL)EN5_RndFrameW / EN5_RndFrameH;
  else
    ry *= (DBL)EN5_RndFrameH / EN5_RndFrameW;

  EN5_RndMatrProj = MatrFrustum(-rx, rx, -ry, ry, 
                      EN5_RndProjDist, EN5_RndProjFarClip);
  EN5_RndMatrVP = MatrMulMatr(EN5_RndMatrView, EN5_RndMatrProj);
} /* End of 'EN5_RndProjSet' function */

/* Set camera function.
 * ARGUMENTS:
 *   - parametr of located:
 *       VEC Loc, VEC At, VEC Up.
 * RETURNS: None.
 */
VOID EN5_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  EN5_RndMatrView = MatrView(Loc, At, Up);
  EN5_RndMatrVP = MatrMulMatr(EN5_RndMatrView, EN5_RndMatrProj);
} /* End of 'EN5_RndCamSet' function */

/* END OF 'RNDBASE.C' FILE */