/* FILE NAME: U_BALLS.C
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "units.h"

typedef struct tagen5UNIT_TANKS
{
  UNIT_BASE_FIELDS;
  en5PRIMS Tanks;
  FLT TowerAngle, BarrelAngle, HullAngle;
  VEC Pos;
  FLT Speed;
  BOOL AutoPilot;
} en5UNIT_TANKS;

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitClose( en5UNIT_TANKS *Uni, en5ANIM *Ani )
{
  EN5_RndPrimsFree(&Uni->Tanks);
} /* End of 'EN5_UnitClose' function */

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT_TANKS *Uni, en5ANIM *Ani )
{
  EN5_RndPrimsLoad(&Uni->Tanks, "Abrams_BF3.g3dm");
} /* End of 'EN5_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT_TANKS *Uni, en5ANIM *Ani )
{
  VEC p;

  Uni->HullAngle += (Ani->Keys['A'] - Ani->Keys['D']) * Ani->GlobalDeltaTime * 50;
 
  if (Ani->KeysClick['Q'])
    Uni->AutoPilot = !Uni->AutoPilot;
  if (Uni->AutoPilot)
    Uni->Speed += (Ani->Keys['W'] - Ani->Keys['S']) * Ani->GlobalDeltaTime * 20;
  else
    Uni->Speed = (Ani->Keys['W'] - Ani->Keys['S']) * Ani->GlobalDeltaTime * 20;

  Uni->TowerAngle += (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]) * Ani->GlobalDeltaTime * 50;
  Uni->BarrelAngle += (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * Ani->GlobalDeltaTime * 20;

  if (Uni->Speed < -0.5)
    Uni->Speed = -0.5;
  if (Uni->Speed > 1)
    Uni->Speed = 1;

  Uni->Pos = VecAddVec(Uni->Pos,
    VecMulNum(VectorTransform(VecSet(0, 0, -1), MatrRotateY(Uni->HullAngle)), Uni->Speed));
  if (Uni->BarrelAngle > 20)
    Uni->BarrelAngle = 20;
  if (Uni->BarrelAngle < -10)
    Uni->BarrelAngle = -10;

  p = VecDivNum(VecAddVec(Uni->Tanks.Prims[1].MinBB, Uni->Tanks.Prims[1].MaxBB), 3);
  Uni->Tanks.Prims[2].Trans = Uni->Tanks.Prims[1].Trans =
    Uni->Tanks.Prims[5].Trans = Uni->Tanks.Prims[6].Trans =
    Uni->Tanks.Prims[13].Trans = Uni->Tanks.Prims[14].Trans =
    Uni->Tanks.Prims[15].Trans = Uni->Tanks.Prims[16].Trans =
    Uni->Tanks.Prims[18].Trans = Uni->Tanks.Prims[0].Trans =
    MatrMulMatr3(MatrTranslate(VecNeg(p)), MatrRotateY(Uni->TowerAngle), MatrTranslate(p));
  p.X = (Uni->Tanks.Prims[1].MinBB.X + Uni->Tanks.Prims[1].MaxBB.X) / 2;
  p.Y = (Uni->Tanks.Prims[1].MinBB.Y + Uni->Tanks.Prims[1].MaxBB.Y) / 2;
  p.Z = Uni->Tanks.Prims[1].MinBB.Z;
  Uni->Tanks.Prims[16].Trans = MatrMulMatr4(MatrTranslate(VecNeg(p)), MatrRotateX(Uni->BarrelAngle), MatrTranslate(p), Uni->Tanks.Prims[16].Trans);

  p = VecDivNum(VecAddVec(Uni->Tanks.Prims[1].MinBB, Uni->Tanks.Prims[1].MaxBB), 3);
  Uni->Tanks.Prims[3].Trans = Uni->Tanks.Prims[4].Trans =
    Uni->Tanks.Prims[7].Trans = Uni->Tanks.Prims[8].Trans =
    Uni->Tanks.Prims[9].Trans = Uni->Tanks.Prims[10].Trans =
    Uni->Tanks.Prims[11].Trans = Uni->Tanks.Prims[12].Trans =
    Uni->Tanks.Prims[19].Trans =
    MatrMulMatr3(MatrTranslate(VecNeg(p)), MatrRotateY(Uni->HullAngle), MatrTranslate(p));
} /* End of 'EN5_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_BALL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT_TANKS *Uni, en5ANIM *Ani )
{
  EN5_RndPrimsDraw(&Uni->Tanks, MatrMulMatr3(MatrTranslate(VecSet(0, 2, 0)), MatrScale(VecSet1(1)), MatrTranslate(Uni->Pos)));
} /* End of 'EN5_UnitRender' function */

/* Unit tanks creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateTanks( VOID )
{
  en5UNIT_TANKS *Uni;

  if ((Uni = (en5UNIT_TANKS *)EN5_AnimUnitCreate(sizeof(en5UNIT_TANKS))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EN5_UnitInit;
  Uni->Response = (VOID *)EN5_UnitResponse;
  Uni->Render = (VOID *)EN5_UnitRender;
  Uni->Close = (VOID *)EN5_UnitClose;
  return (en5UNIT *)Uni;
} /* End of 'EN5_UnitCreateBall' function */

/* END OF 'U_BALLS.C' FILE */