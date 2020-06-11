/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: EN5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system primitive handle function
 */
#include <string.h>
#include <stdio.h>

#include "rnd.h"

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
VOID EN5_RndPrimCreate( en5PRIM *Pr, en5VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  memset(Pr, 0, sizeof(en5PRIM));

  if (V != NULL)
  {
    /* Generate vertex array and vertex buffer */
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    /* Fill vertex buffer */
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(en5VERTEX) * NoofV, V, GL_STATIC_DRAW);

    /* Setup vertex array  */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(en5VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(en5VERTEX),
                          (VOID *)sizeof(VEC)); /* texture cootdinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(en5VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(en5VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    Pr->NumOfElements = NoofV;
  }

  if (I != NULL)
  {
    /* Generate index buffer */
    glGenBuffers(1, &Pr->IBuf);

    /* Fill index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);

    Pr->NumOfElements = NoofI;
  }

  Pr->Trans = MatrIdentity();
} /* End of 'EN5_RndPrimCreate' function */


/* Free primitive memory function.
 * ARGUMENTS:
 *   - pointer to primitive to free:
 *       en5PRIM *Pr;
 * RETURNS: None.
 */
VOID EN5_RndPrimFree( en5PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  glDeleteVertexArrays(1, &Pr->IBuf);
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

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.M[0]);

  /* Draw primitive */
  glBindVertexArray(Pr->VA);

  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
  }
  else
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
  glBindVertexArray(0);
} /* End of 'EN5_RndPrimDraw' function */

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
BOOL EN5_RndPrimCreateSphere( en5PRIM *Pr, VEC C, DBL RX, DBL RY, DBL RZ, INT SplitW, INT SplitH )
{
  DBL theta, phi;
  INT i, j, k, f;
  INT size;
  en5VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(en5PRIM));
  size = sizeof(en5VERTEX) * SplitW * SplitH + sizeof(INT) * (SplitW - 1) * (SplitH - 1) * 2 * 3;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + SplitW * SplitH);

  /* Build vertex array */
  for (theta = 0, i = 0, k = 0; i < SplitH; i++, theta += PI / (SplitH - 1))
    for (phi = 0, j = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
      V[k++].P = VecSet(C.X + RX * cos(phi) * sin(theta),
                            C.Y + RY * cos(theta),
                            C.Z + RZ * sin(phi) * sin(theta));

  /* Build index array */
  for (i = 0, k = 0, f = 0; i < SplitH - 1; i++, k++)
    for (j = 0; j < SplitW - 1; j++, k++)
    {
      /* first triangle */
      Ind[f++] = k;
      Ind[f++] = k + 1;
      Ind[f++] = k + SplitW;

      /* second triangle */
      Ind[f++] = k + SplitW;
      Ind[f++] = k + 1;
      Ind[f++] = k + SplitW + 1;
    }

  EN5_RndPrimCreate(Pr, V, SplitW * SplitH, Ind, (SplitW - 1) * (SplitH - 1) * 2 * 3);
  return TRUE;
} /* End of 'EN5_RndPrimCreateSphere' function */

/* Create prim of top function 
 * ARGUMENTS:
 *   - prim struct:
 *       en5PRIM *Pr.
 *   - centr coordinate:
 *       VEC C.
 *   - radius
 *       DBL R, r.
 *   - number of segments.
 *       INT SplitW, INT SplitH
 * RETURNS:
 *   (BOOL) work.
 */
BOOL EN5_RndPrimCreateTop( en5PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH )
{
  DBL theta, phi;
  INT i, j, k, f;
  INT size;
  en5VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(en5PRIM));
  size = sizeof(en5VERTEX) * SplitW * SplitH + sizeof(INT) * (SplitW - 1) * (SplitH - 1) * 2 * 3;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + SplitW * SplitH);

  /* Build vertex array */
  for (theta = 0, i = 0, k = 0; i < SplitH; i++, theta += 2 * PI / (SplitH - 1))
    for (phi = 0, j = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
      V[k++].P = VecSet(C.X + (R + r * cos(theta)) * cos(phi),
                            C.Y + r * sin(theta),
                            C.Z + (R + r * cos(theta)) * sin(phi));

  /* Build index array */
  for (i = 0, k = 0, f = 0; i < SplitH - 1; i++, k++)
    for (j = 0; j < SplitW - 1; j++, k++)
    {
      /* first triangle */
      Ind[f++] = k;
      Ind[f++] = k + 1;
      Ind[f++] = k + SplitW;

      /* second triangle */
      Ind[f++] = k + SplitW;
      Ind[f++] = k + 1;
      Ind[f++] = k + SplitW + 1;
    }

  EN5_RndPrimCreate(Pr, V, SplitW * SplitH, Ind, (SplitW - 1) * (SplitH - 1) * 2 * 3);
  return TRUE;
} /* End of 'EN5_RndPrimCreateSphere' function */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_RndPrimLoad(en5PRIM *Pr, CHAR *FileName )
{
  INT vn = 0, fn = 0;
  FILE *F;
  CHAR Buf[1000];
  en5VERTEX *V;
  INT *Ind, size;

  memset(Pr, 0, sizeof(en5PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and index quantities */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      vn++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      fn++;
  }

  size = sizeof(en5VERTEX) * vn + sizeof(INT) * fn * 3;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + vn);

  /* Read vertices and facets data */
  rewind(F);
  vn = fn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[vn++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      /* Read one of possible facet references */
      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      Ind[fn++] = n1 - 1;
      Ind[fn++] = n2 - 1;
      Ind[fn++] = n3 - 1;
    }
  }
  EN5_RndPrimCreate(Pr, V, vn, Ind, fn);

  fclose(F);
  free(V);
  return TRUE;
} /* End of 'EN5_RndPrimLoad' function */

/* END OF 'RNDPRIM.C' FILE */