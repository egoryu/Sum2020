/* FILE NAME: T04PERM.C
 * PROGRAMMER: EN5
 * DATE: 02.06.2020
 * PURPOSE: permutation.
 */

#include <stdio.h>

#include <windows.h>

/* Permutation array */
#define MAX 6

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
  INT i, x;
  BOOL SaveParity;

  if (Pos == MAX)
    Store();
  else
  {
    SaveParity = IsParity;
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      /* Put in Pos element i*/
      if (Pos != i)
      {
        Swap(&P[Pos], &P[i]);
        IsParity = !IsParity;
      }
      Go(Pos + 1);
    }
    x = P[Pos];
    for (i = Pos + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = x;
    IsParity = SaveParity;
  }
} /* End of 'Go' function */

/* Main program function */
VOID main( VOID )
{
  INT i, Pos = 0;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;

  Go(0);
} /* End of 'main' function */

/* END OF 'T04PERM.C' FILE */