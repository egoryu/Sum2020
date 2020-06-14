/* FILE NAME  : U_CTRL.C
 * PROGRAMMER : EN5
 * LAST UPDATE: 09.06.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Control unit sample.
 */

#include <stdio.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagen5UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  DBL
    Distance,      /* Camera offset */
    RotateAngle,   /* Camera rotate angle */
    ElevatorAngle; /* Camera elevator angle */
  en5PRIM Axes;
} en5UNIT_CTRL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_CTRL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT_CTRL *Uni, en5ANIM *Ani )
{
  en5VERTEX V[] = 
    {
      {{0, 0, 0}, {0, 0}, {0, 0, 0}, {1, 0, 0, 1}},
      {{3000, 0, 0}, {0, 0}, {0, 0, 0}, {1, 0, 0, 1}},
      {{0, 0, 0}, {0, 0}, {0, 0, 0}, {0, 1, 0, 1}},
      {{0, 3000, 0}, {0, 0}, {0, 0, 0}, {0, 1, 0, 1}},
      {{0, 0, 0}, {0, 0}, {0, 0, 0}, {0, 0, 1, 1}},
      {{0, 0, 3000}, {0, 0}, {0, 0, 0}, {0, 0, 1, 1}}
    };
  INT Ind[] = {0, 1, 2, 3, 4, 5};
  en5MATERIAL mtl = EN5_RndMaterials[0];

  EN5_RndPrimCreate(&Uni->Axes, EN5_RND_PRIM_LINES, V, 6, Ind, 6);
  mtl.ShdNo = EN5_RndShaderAdd("0");
  Uni->Axes.MtlNo = EN5_RndMtlAdd(&mtl);
  Uni->RotateAngle = 30;
  Uni->ElevatorAngle = 47;
  Uni->Distance = 4;
} /* End of 'EN5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_CTRL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitClose( en5UNIT_CTRL *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_CTRL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT_CTRL *Uni, en5ANIM *Ani )
{
  VEC L = VecSet(0, 0, Uni->Distance);
  static CHAR Buf[102];
  static DBL Mzk = 0.2;

  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
    EN5_FlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    ;//EN5_AnimDoExit();
  if (Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['S'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (Ani->Keys['A'])
    Mzk = 15;
  else
    Mzk = 0.2;

  Uni->Distance += Ani->GlobalDeltaTime * Ani->Mdz * Mzk;
  if (Ani->Keys[VK_LBUTTON])
  {
    Uni->RotateAngle += Ani->GlobalDeltaTime * 15 * Ani->Mdx;
    Uni->ElevatorAngle += Ani->GlobalDeltaTime * 15 * Ani->Mdy;
  }
  L = PointTransform(L,
    MatrMulMatr3(MatrRotateZ(-Uni->Distance),
                 MatrRotateX(-Uni->ElevatorAngle),
                 MatrRotateY(-Uni->RotateAngle)));
  EN5_RndCamSet(L, VecSet(0, 0, 0), VecSet(0, 1, 0));

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);
} /* End of 'EN5_UnitResponse' function */

/* U  nit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_CTRL *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT_CTRL *Uni, en5ANIM *Ani )
{
  glLineWidth(18);
  EN5_RndPrimDraw(&Uni->Axes, MatrIdentity());
  glLineWidth(1);
} /* End of 'EN5_UnitRender' function */

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (en5UNIT_CTRL *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateControl( VOID )
{
  en5UNIT_CTRL *Uni;

  /* Memory allocation */
  if ((Uni = (en5UNIT_CTRL *)EN5_AnimUnitCreate(sizeof(en5UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)EN5_UnitInit;
  Uni->Close = (VOID *)EN5_UnitClose;
  Uni->Response = (VOID *)EN5_UnitResponse;
  Uni->Render = (VOID *)EN5_UnitRender;
  return (en5UNIT *)Uni;
} /* End of 'EN5_UnitCreateControl' function */

/* END OF 'U_CTRL.C' FILE */