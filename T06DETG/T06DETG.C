/* FILE NAME: T06DETG.C
 * PROGRAMMER: EN5
 * DATE: 03.06.2020
 * PURPOSE: dertiminat gaus.
 */
#include <windows.h>

#include <stdio.h>
#include <math.h>
#include <conio.h>

#define MAX 10

DOUBLE A[MAX][MAX];
INT N;

INT P[MAX];
BOOL IsParity;

/* Swap two elements function */
VOID Swap( DOUBLE *A, DOUBLE *B )
{
  DOUBLE tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Load matrix function */
BOOL LoadMaxtrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* End of 'LoadMaxtrix' function */

/* Count determinate function */
DOUBLE DetG( VOID )
{
  DOUBLE Det = 1, coef;
  INT i, max_row, max_col;

  for (i = 0; i < N; i++)
  {
    INT x, y, k, z;

    max_col = max_row = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
    if (A[max_row][max_col] == 0)
    {
      Det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[i][x], &A[max_row][x]);
      Det = -Det;
    }
    if (max_col != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[x][i], &A[x][max_col]);
      Det = -Det;
    }
    coef = A[i + 1][i] / A[i][i];
    A[i + 1][i] = 0;
    for (k = i + 1; k < N; k++)
      A[i + 1][k] -= A[i][k] * coef;
    for (z = 1; z < N - 1; z++)
    {
      coef = A[i + 1 + z][i] / A[i][i];
      for (k = i; k < N; k++)
        A[i + 1 + z][k] -= A[i][k] * coef;
    }
    Det *= A[i][i];
  }
  return Det;
} /* End of 'DetG' function */

/* Main program function */
VOID main( VOID )
{
  LoadMaxtrix("IN.TXT");
  printf("%f", DetG());
  _getch();
} /* End of 'main' function */

/* END OF 'T06DETG.C' FILE */