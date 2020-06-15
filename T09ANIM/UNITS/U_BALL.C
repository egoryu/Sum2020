/* FILE NAME: U_BALLS.C
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "units.h"

typedef struct tagen5UNIT_BALL
{
  UNIT_BASE_FIELDS;
  en5PRIM Ball;
  en5PRIMS Car;
} en5UNIT_BALL;

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitClose( en5UNIT_BALL *Uni, en5ANIM *Ani )
{
  EN5_RndPrimsFree(&Uni->Car);
  EN5_RndPrimFree(&Uni->Ball);
} /* End of 'EN5_UnitClose' function */

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT_BALL *Uni, en5ANIM *Ani )
{
  //EN5_RndPrimCreateTop(&Uni->Ball, VecSet(0, 0, 0), 3, 1, 40, 30);
  en5MATERIAL mtl = EN5_RndMaterials[0];

  EN5_RndPrimCreateSphere(&Uni->Ball, VecSet1(0), 500, 500, 500, 8 * 18, 8 * 18);
  //mtl.Tex[0] = EN5_RndTexAddG24("P06.G24");
  mtl.Tex[0] = EN5_RndTexAddBMP("sky.bmp");
  mtl.Ka = VecSet1(0);
  mtl.Kd = VecSet1(0.9);
  mtl.Ks = VecSet1(0.9);
  mtl.Ph = 1;
  mtl.ShdNo = EN5_RndShaderAdd("SKY");
  Uni->Ball.MtlNo = EN5_RndMtlAdd(&mtl);

  EN5_RndPrimsLoad(&Uni->Car, "c172.g3dm");
} /* End of 'EN5_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT_BALL *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT_BALL *Uni, en5ANIM *Ani )
{
  EN5_RndPrimsDraw(&Uni->Car, MatrMulMatr(MatrTranslate(VecSet(0, 2, 0)), MatrScale(VecSet1(3))));
  EN5_RndPrimDraw(&Uni->Ball, MatrIdentity());
} /* End of 'EN5_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateBall( VOID )
{
  en5UNIT_BALL *Uni;

  if ((Uni = (en5UNIT_BALL *)EN5_AnimUnitCreate(sizeof(en5UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EN5_UnitInit;
  Uni->Response = (VOID *)EN5_UnitResponse;
  Uni->Render = (VOID *)EN5_UnitRender;
  Uni->Close = (VOID *)EN5_UnitClose;
  return (en5UNIT *)Uni;
} /* End of 'EN5_UnitCreateBall' function */

/* END OF 'U_BALLS.C' FILE */