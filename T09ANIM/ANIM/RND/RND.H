/* FILE NAME: RND.H
 * PROGRAMMER: EN5
 * DATE: 05.06.2020
 * PURPOSE: 3D animation project.
 *          Common declaration module.
 */

#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include "glew.h"
#include <gl/gl.h>
#include <glut.h>

#include "res/rndres.h"
#include "../../def.h"

/* render data */
extern HWND EN5_hRndWnd;        /* Work window handle */
extern HDC EN5_hRndDC;     /* Work window memory device context */
extern HGLRC EN5_hRndGLRC;
extern INT EN5_RndFrameH, EN5_RndFrameW; /* Work window size */

extern DBL
  EN5_RndProjSize,  /* Project plane fit square */
  EN5_RndProjDist,  /* Distance to project plane from viewer (near) */
  EN5_RndProjFarClip;  /* Distance to project far clip plane (far) */


extern MATR
  EN5_RndMatrView, /* View coordinate system matrix */
  EN5_RndMatrProj, /* Projection coordinate system matrix */
  EN5_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC EN5_RndCamLoc;
/* vertex type */
typedef struct tagen5VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinate */
  VEC N;  /* Vertex normal position */
  VEC4 C; /* color */
} en5VERTEX;

/* Primitive type */
typedef enum tagen5PRIM_TYPE
{
  EN5_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  EN5_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  EN5_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  EN5_RND_PRIM_POINTS,   /* Arrauy of points */
} en5PRIM_TYPE;


/* Primitive representation type */
typedef struct tagen5PRIM
{
  INT
    VA,              /* OpenGL vertex array identifier */
    VBuf,            /* OpenGL vertex buffer identifier */
    IBuf;            /* OpenGL index buffer identifier */
  INT NumOfElements; /* Number of vertices or indices */
  MATR Trans;        /* Additional transformation matrix */
  en5PRIM_TYPE Type; /* Primitive type */
  INT MtlNo; /* Material number in material array */
} en5PRIM;


/* Render system initialization function.
 * ARGUMENTS:
 *   - HWND:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_RndInit( HWND hWnd );

/* Render system close function.
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

/* Copy frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndCopyFrame( VOID );

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
 *   - pointer to primitive to create:
 *       en5PRIM *Pr;
 *   - new primitive vertex array:
 *       en5VERTEX *V;
 *   - new primitive vertex array size:
 *       INT NoofV;
 *   - new primitive index array:
 *       INT *I;
 *   - new primitive index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID EN5_RndPrimCreate( en5PRIM *Pr, en5PRIM_TYPE Type, en5VERTEX *V, INT NoofV, INT *I, INT NoofI );

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
 *       DBL RX, RY, RZ.
 *   - number of segments.
 *       INT SplitW, INT SplitH
 * RETURNS:
 *   (BOOL) work.
 */
BOOL EN5_RndPrimCreateSphere( en5PRIM *Pr, VEC C, DBL RX, DBL RY, DBL RZ, INT SplitW, INT SplitH );

/* Create prim of top function 
 * ARGUMENTS:
 *   - prim struct:
 *       en5PRIM *Pr.
 *   - centr coordinate:
 *       VEC C.
 *   - radius
 *       DBL RX, r.
 *   - number of segments.
 *       INT SplitW, INT SplitH
 * RETURNS:
 *   (BOOL) work.
 */
BOOL EN5_RndPrimCreateTop( en5PRIM *Pr, VEC C, DBL RX, DBL r, INT SplitW, INT SplitH );

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       en5PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_RndPrimLoad(en5PRIM *Pr, CHAR *FileName );

/* Create grid primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       en5PRIM *Pr;
 *   - new primitive vertex array:
 *       en5VERTEX *V;
 *   - size of grid:
 *       INT W, H;
 *   - need or nor normolize:
 *       BOOL NeedNorm;
 * RETURNS: None.
 */
BOOL EN5_RndPrimCreateFromGrid( en5PRIM *Pr, en5VERTEX *V, INT W, INT H, BOOL NeedNorm );

#endif /* __RND_H_ */

/* END OF 'RND.H' FILE */