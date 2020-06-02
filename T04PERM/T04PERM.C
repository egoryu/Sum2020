/* FILE NAME: T04PERM.C
 * PROGRAMMER: EN5
 * DATE: 02.06.2020
 * PURPOSE: permutation.
 */

#include <stdio.h>

#include <windows.h>

/* Permutation array */
#define MAX 3

INT P[MAX];
BOOL IsParity;

/* Change two elements function */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Store permutation to log file function */
VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;

  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d – parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");

  fclose(F);
} /* End of 'Store' function */

/* Build permutation function */
VOID Go( INT Pos )
{
  INT i;

  if (Pos == MAX - 1)
    Store();
  else
  {
    for (i = Pos; i < MAX; i++)
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

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;

  Go(0);
} /* End of 'main' function */

/* END OF 'T04PERM.C' FILE */