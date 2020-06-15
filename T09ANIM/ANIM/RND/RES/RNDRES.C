/* FILE NAME: RNDRES.C
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Resurses module.
 */
#include "rndres.h"

/* Initialization resurse struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndResInit( VOID )
{
  EN5_RndMtlInit();
  EN5_RndTexInit();
}

/* Deinitialization resurse struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndResClose( VOID )
{
  INT i;

  EN5_RndMtlClose();
  EN5_RndTexClose();
  for (i = 0; i < EN5_RndShadersSize; i++)
    EN5_RndShdDelete(i);
}

/* END OF 'RNDRES.C' FILE */