/* FILE NAME: T05DET.C
 * PROGRAMMER: EN5
 * DATE: 03.06.2020
 * PURPOSE: dertiminat.
 */

#include <stdio.h>

#include <windows.h>

/* Permutation array */
#define MAX 10
DOUBLE A[MAX][MAX];
INT N;
DOUBLE Det = 0;

INT P[MAX];
BOOL IsParity = TRUE;

/* Load maxtrix function */
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
  else if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* End of 'LoadMaxtrix' function */

/* Change two elements function */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Build permutation function */
VOID Go( INT Pos )
{
  INT i;
  DOUBLE prod;

  if (Pos == N)
  {
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][P[i]];
    Det += (IsParity ? 1 : -1) * prod;
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        IsParity = !IsParity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        IsParity = !IsParity;
    }
  }
} /* End of 'Go' function */

/* Main program function */
VOID main( VOID )
{
  INT i;

  LoadMaxtrix("Matrix.in");

  for (i = 0; i < N; i++)
    P[i] = i;

  Go(0);
  printf("%f", Det);
  getch();
} /* End of 'main' function */

/* END OF 'T05DET.C' FILE */