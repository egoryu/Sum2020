/* FILE NAME: RNDBASE.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system render handle function
 */

#include <time.h>

#include "rnd.h"

#pragma comment(lib, "opengl32")

/* Render system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  EN5_hRndWnd = hWnd;
  EN5_hRndDC = GetDC(hWnd);

  /* OpenGL initialization */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(EN5_hRndDC, &pfd);
  DescribePixelFormat(EN5_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(EN5_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  EN5_hRndGLRC = wglCreateContext(EN5_hRndDC);
  wglMakeCurrent(EN5_hRndDC, EN5_hRndGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  glClearColor(1, 1, 1, 1);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  /* default parametrs */
  EN5_RndResInit();

  EN5_RndFrameH = 102;
  EN5_RndFrameW = 102;

  EN5_RndProjSize = EN5_RndProjDist = 1.0;
  EN5_RndProjFarClip = 3000;

  EN5_RndProjSet();
  EN5_RndCamSet(VecSet(3, 3, 3), VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'EN5_RndInit' function */

/* Render systen initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndClose( VOID )
{
  EN5_RndResClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(EN5_hRndGLRC);
} /* End of 'EN5_RndClose' function */

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID EN5_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* save size */
  EN5_RndFrameW = W;
  EN5_RndFrameH = H;

  /* recalculat project */
  EN5_RndProjSet();
} /* End of 'EN5_RndResize' function */

/* Copy frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndCopyFrame( VOID )
{
  SwapBuffers(EN5_hRndDC);
} /* End of 'EN5_RndCopyFrame' function */

/* Start draw function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndStart( VOID )
{
  LONG t;
  static LONG save_t = -1;

  t = clock();
  if (t - save_t > 2 * CLOCKS_PER_SEC)
    EN5_RndShadersUpdate();

  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

} /* End of 'EN5_RndStart' function */

/* End draw function 
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID EN5_RndEnd( VOID )
{
  glFinish();
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
  EN5_RndCamLoc = Loc;
  EN5_RndMatrView = MatrView(Loc, At, Up);
  EN5_RndMatrVP = MatrMulMatr(EN5_RndMatrView, EN5_RndMatrProj);
} /* End of 'EN5_RndCamSet' function */

/* END OF 'RNDBASE.C' FILE */