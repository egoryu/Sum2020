/* FILE NAME: RND.H
 * PROGRAMMER: EN5
 * DATE: 05.06.2020
 * PURPOSE: 3D animation project.
 *          Common declaration module.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

/* render data */
extern HWND EN5_hRndWnd;        /* Work window handle */
extern HDC EN5_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP EN5_hRndBmFrame; /* Work window background bitmap handle */
extern INT EN5_RndFrameH, EN5_RndFrameW; /* Work window size */

extern DBL
  EN5_RndProjSize,  /* Project plane fit square */
  EN5_RndProjDist,  /* Distance to project plane from viewer (near) */
  EN5_RndProjFarClip;  /* Distance to project far clip plane (far) */


extern MATR
  EN5_RndMatrView, /* View coordinate system matrix */
  EN5_RndMatrProj, /* Projection coordinate system matrix */
  EN5_RndMatrVP;   /* Stored (View * Proj) matrix */

/* vertex type */
typedef struct tagen5VERTEX
{
  VEC P;  /* Vertex position */
} en5VERTEX;

/* primitiv type */
typedef struct tagen5PRIM
{
  en5VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} en5PRIM;

/* Render systen initialization function.
 * ARGUMENTS:
 *   - HWND:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_RndInit( HWND hWnd );

/* Render systen initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndClose( VOID );

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID EN5_RndResize( INT W, INT H );

/* Change window size function.
 * ARGUMENTS:
 *   - window:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID EN5_RndCopyFrame( HDC hDC );

/* Start draw function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndStart( VOID );

/* End draw function 
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID EN5_RndEnd( VOID );

/* Create camera function.
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID EN5_RndProjSet( VOID );

/* Set camera function.
 * ARGUMENTS:
 *   - parametr of located:
 *       VEC Loc, VEC At, VEC Up.
 * RETURNS: None.
 */
VOID EN5_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       en5PRIM *Pr.
 *   - number of vertices:
 *       INT NoofV.
 *   - number of index:
 *       INT NoofI.
 * RETURNS:
 *   (BOOL) work.
 */
BOOL EN5_RndPrimCreate( en5PRIM *Pr, INT NoofV, INT NoofI );

/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       en5PRIM *Pr.
 * RETURNS: None.
 */
VOID EN5_RndPrimFree( en5PRIM *Pr );

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       en5PRIM *Pr.
 *   - wotld matrix:
 *       MATR Wolrd.
 * RETURNS:
 *   (BOOL) work.
 */
VOID EN5_RndPrimDraw( en5PRIM *Pr, MATR World );

/* Create prim of sphere function 
 * ARGUMENTS:
 *   - prim struct:
 *       en5PRIM *Pr.
 *   - centr coordinate:
 *       VEC C.
 *   - radius
 *       DBL R.
 *   - number of segments.
 *       INT SplitW, INT SplitH
 * RETURNS:
 *   (BOOL) work.
 */
BOOL EN5_RndPrimCreateSphere( en5PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

#endif /* __DEF_H_ */

/* END OF 'RND.H' FILE */