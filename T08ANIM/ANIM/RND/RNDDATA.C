/* FILE NAME: RNDDATA.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system global data
 */

#include "rnd.h"

HWND EN5_hRndWnd;        /* Work window handle */
HDC EN5_hRndDCFrame;     /* Work window memory device context  */
HBITMAP EN5_hRndBmFrame; /* Work window background bitmap handle */
INT EN5_RndFrameH, EN5_RndFrameW; /* Work window size */

DBL
  EN5_RndProjSize,  /* Project plane fit square */
  EN5_RndProjDist,  /* Distance to project plane from viewer (near) */
  EN5_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  EN5_RndMatrView, /* View coordinate system matrix */
  EN5_RndMatrProj, /* Projection coordinate system matrix */
  EN5_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'RNDDATA.C' FILE */