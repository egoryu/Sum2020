/* FILE NAME: GLOBE.H
 * PROGRAMMER: EN5
 * DATE: 04.06.2020
 * PURPOSE: draw 3D object.
 */

#define PI 3.14159265358979323846

#define GLOBE_W 15
#define GLOBE_H 15

typedef double DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

VOID GlobeSet( DBL R );
VOID GlobeDraw( HDC hDC, DBL Xc, DBL Yc );
/* END OF 'GLOBE.H' FILE */