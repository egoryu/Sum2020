/* FILE NAME: U_COW.C
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "../anim/anim.h"

typedef struct tagen5UNIT_COW
{
  UNIT_BASE_FIELDS;
  en5PRIM Ball;
  VEC Pos;
} en5UNIT_COW;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_COW *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT_COW *Uni, en5ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
  EN5_RndPrimLoad(&Uni->Ball, "cow.obj");
} /* End of 'EN5_UnitInit' function */
/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_COW *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT_COW *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_COW *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT_COW *Uni, en5ANIM *Ani )
{
  EN5_RndPrimDraw(&Uni->Ball, MatrMulMatr3(MatrScale(VecSet(0.5, 0.5, 0.5)), MatrTranslate(VecSet(1, 0, 1)), MatrRotateX(30 * sin(EN5_Anim.Time * 8))));
} /* End of 'EN5_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateCow( VOID )
{
  en5UNIT_COW *Uni;

  if ((Uni = (en5UNIT_COW *)EN5_AnimUnitCreate(sizeof(en5UNIT_COW))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)EN5_UnitInit;
  Uni->Response = (VOID *)EN5_UnitResponse;
  Uni->Render = (VOID *)EN5_UnitRender;
  return (en5UNIT *)Uni;
} /* End of 'EN5_UnitCreateCow' function */

/* END OF 'U_COW.C' FILE */