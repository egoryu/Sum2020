/* FILE NAME: GLOBE.C
 * PROGRAMMER: EN5
 * DATE: 04.06.2020
 * PURPOSE: draw 3D object.
 */
#include <stdlib.h>

#include <windows.h>

#include "globe.h"
#include "timer.h"

VEC Geom[GLOBE_H][GLOBE_W];

/* Create globe function */
VOID GlobeSet( DBL R )
{
  DBL The = 0, Phi = 0;
  INT i, j;

  for (The = 0, i = 0; i < GLOBE_H; i++, The += PI / (GLOBE_H - 1))
    for (Phi = 0, j = 0; j < GLOBE_W; j++, Phi += 2 * PI / (GLOBE_W - 1))
    {
      Geom[i][j].X = R * sin(The) * sin(Phi);
      Geom[i][j].Y = R * cos(The);
      Geom[i][j].Z = R * sin(The) * cos(Phi);
    }
} /* End of 'GlobeSet' function */

/* Draw globe function */
VOID GlobeDraw( HDC hDC, DBL Xc, DBL Yc )
{
  INT i, j;
  DBL s = 4;
  static VEC Geom1[GLOBE_H][GLOBE_W];
  DBL t = GlobalTime;

  /* Rotate globe */
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
      Geom1[i][j] = VecMulMatr(Geom[i][j], MatrMulMatr(MatrRotateY(t * 8), MatrRotateZ(t * 10)));

#if 0
  /* Draw pixel globe */
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(255, 0, 0));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 0, 0));

  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
      Ellipse(hDC, (INT)(Geom1[i][j].X + Xc - s), (INT)(Geom1[i][j].Y + Yc - s), (INT)(Geom1[i][j].X + Xc + s), (INT)(Geom1[i][j].Y + Yc + s));

  /* Draw line globe */
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(255, 0, 0));

  /* vertical */
  for (j = 0; j < GLOBE_W; j++)
  {
    MoveToEx(hDC, (INT)(Geom1[0][j].X + Xc), (INT)(Geom1[0][j].Y + Yc), NULL);
    for (i = 1; i < GLOBE_H; i++)
      LineTo(hDC, (INT)(Geom1[i][j].X + Xc), (INT)(Geom1[i][j].Y + Yc));
  }
  /* gorizontal */
  for (j = 0; j < GLOBE_H; j++)
  {
    MoveToEx(hDC, (INT)(Geom1[j][0].X + Xc), (INT)(Geom1[j][0].Y + Yc), NULL);
    for (i = 1; i < GLOBE_W; i++)
      LineTo(hDC, (INT)(Geom1[j][i].X + Xc), (INT)(Geom1[j][i].Y + Yc));
  }
#endif
  /* Draw poligon globe */
  srand(30);
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(255, 255, 255));

  for (i = 0; i < GLOBE_H - 1; i++)
    for (j = 0; j < GLOBE_W - 1; j++)
    {
      POINT pnts[] = {{(LONG)(Geom1[i][j].X + Xc), (LONG)(Geom1[i][j].Y + Yc)}, {(LONG)(Geom1[i + 1][j].X + Xc), (LONG)(Geom1[i + 1][j].Y + Yc)},
      {(LONG)(Geom1[i + 1][j + 1].X + Xc), (LONG)(Geom1[i + 1][j + 1].Y + Yc)}, {(LONG)(Geom1[i][j + 1].X + Xc), (LONG)(Geom1[i][j + 1].Y + Yc)}};

      if ((pnts[0].x - pnts[1].x) * (pnts[0].y + pnts[1].y) +
          (pnts[1].x - pnts[2].x) * (pnts[1].y + pnts[2].y) +
          (pnts[2].x - pnts[3].x) * (pnts[2].y + pnts[3].y) +
          (pnts[3].x - pnts[0].x) * (pnts[3].y + pnts[0].y) > 0)
          {
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
            Polygon(hDC, pnts, 4);
          }
    }
} /* End of 'GlobeDraw' function */

/* END OF 'GLOBE.C' FILE */