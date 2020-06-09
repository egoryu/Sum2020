/* FILE NAME: UNIT.C
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitClose( en5UNIT *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_AnimUnitCreate( INT Size )
{
  en5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(en5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = EN5_UnitInit;
  Uni->Close = EN5_UnitClose;
  Uni->Response = EN5_UnitResponse;
  Uni->Render = EN5_UnitRender;

  return Uni;
} /* End of 'EN5_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */