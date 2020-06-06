/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system primitive handle function
 */
#include <string.h>

#include "rnd.h"

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
BOOL EN5_RndPrimCreate( en5PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(en5PRIM));
  size = sizeof(en5VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
} /* End of 'EN5_RndPrimCreate' function */

/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       en5PRIM *Pr.
 * RETURNS: None.
 */
VOID EN5_RndPrimFree( en5PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(en5PRIM));
} /* End of 'EN5_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       en5PRIM *Pr.
 *   - wotld matrix:
 *       MATR Wolrd.
 * RETURNS:
 *   (BOOL) work.
 */
VOID EN5_RndPrimDraw( en5PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, EN5_RndMatrVP);
  POINT *pnts;
  INT i;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * EN5_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * EN5_RndFrameH / 2);
  }

  SelectObject(EN5_hRndDCFrame, GetStockObject(BLACK_PEN));
  /* Draw triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(EN5_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(EN5_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(EN5_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(EN5_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
} /* End of 'EN5_RndPrimDraw' function */

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
BOOL EN5_RndPrimCreateSphere( en5PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  DBL theta, phi;
  INT i, j, k, f;

  /* Create sphere premitive */
  if (!EN5_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * (SplitH - 1) * 2 * 3))
    return FALSE;

  /* Build vertex array */
  for (theta = 0, i = 0, k = 0; i < SplitH; i++, theta += PI / (SplitH - 1))
    for (phi = 0, j = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
      Pr->V[k++].P = VecSet(C.X + R * sin(phi) * sin(theta),
                            C.Y + R * cos(theta),
                            C.Z + R * cos(phi) * sin(theta));

  /* Build index array */
  for (i = 0, k = 0, f = 0; i < SplitH - 1; i++, k++)
    for (j = 0; j < SplitW - 1; j++, k++)
    {
      /* first triangle */
      Pr->I[f++] = k;
      Pr->I[f++] = k + 1;
      Pr->I[f++] = k + SplitW;

      /* second triangle */
      Pr->I[f++] = k + SplitW;
      Pr->I[f++] = k + 1;
      Pr->I[f++] = k + SplitW + 1;
    }

  return TRUE;
} /* End of 'EN5_RndPrimCreateSphere' function */

/* END OF 'RNDPRIM.C' FILE */