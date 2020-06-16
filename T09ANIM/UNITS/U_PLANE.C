/* FILE NAME: U_PLANE.C
 * PROGRAMMER: EN5
 * DATE: 12.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "units.h"
#include "../anim/rnd/res/image.h"

typedef struct tagen5UNIT_PLANE
{
  UNIT_BASE_FIELDS;
  en5PRIM Plane;
} en5UNIT_PLANE;

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_PLANE *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitClose( en5UNIT_PLANE *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitClose' function */

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_PLANE *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitInit( en5UNIT_PLANE *Uni, en5ANIM *Ani )
{
  en5IMAGE img1, img2;
  en5VERTEX *V;
  INT x, y, b, g, r, a, d;
  en5MATERIAL mtl = EN5_RndMaterials[0];

  if (EN5_ImgLoad(&img1, "hf.bmp") && EN5_ImgLoad(&img2, "hftex.bmp") && (V = malloc(sizeof(en5VERTEX) * img1.H * img1.W)) != NULL)
  {
    for (y = 0; y < img1.H; y++)
      for (x = 0; x < img1.W; x++)
      {
        b = img2.Pixels[(img2.W * y + x) * 4 + 0];
        g = img2.Pixels[(img2.W * y + x) * 4 + 1];
        r = img2.Pixels[(img2.W * y + x) * 4 + 2];
        a = img2.Pixels[(img2.W * y + x) * 4 + 3];
        
        d = img1.Pixels[(img1.W * y + x) * 4 + 1];

        V[img1.W * y + x].P = VecSet(x - img1.W / 2, d - 12, img1.H / 2 - y);
        V[img1.W * y + x].C = Vec4Set(r / 255.0, g / 255.0, b / 255.0, 1);
      }
    EN5_RndPrimCreateFromGrid(&Uni->Plane, V, img1.W, img1.H, TRUE);
    mtl.ShdNo = EN5_RndShaderAdd("NORMAL");
    Uni->Plane.MtlNo = EN5_RndMtlAdd(&mtl);
  }

  EN5_ImgFree(&img1);
  EN5_ImgFree(&img2);
  free(V);
 /* INT i, j;
  static en5VERTEX V[GRID_H][GRID_W];

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      DBL a = j / (GRID_W - 1.0), b = i / (GRID_H - 1.0);

      V[i][j].P = VecSet(j - GRID_W / 2, sin(a * 15) * cos(b * 15) * 2, GRID_H / 2 - i);
      V[i][j].C = Vec4Set(0, 1, 0, 1);
    }
    EN5_RndPrimCreateFromGrid(&Uni->Plane, V[0], GRID_W, GRID_H, TRUE);*/
} /* End of 'EN5_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_PLANE *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitResponse( en5UNIT_PLANE *Uni, en5ANIM *Ani )
{
} /* End of 'EN5_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       en5UNIT_PLANE *Uni;
 *   - animation context:
 *       en5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EN5_UnitRender( en5UNIT_PLANE *Uni, en5ANIM *Ani )
{
  EN5_RndPrimDraw(&Uni->Plane, MatrIdentity());
} /* End of 'EN5_UnitRender' function */

/* Unit plane creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreatePlane( VOID )
{
  en5UNIT_PLANE *Uni;

  if ((Uni = (en5UNIT_PLANE *)EN5_AnimUnitCreate(sizeof(en5UNIT_PLANE))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EN5_UnitInit;
  Uni->Response = (VOID *)EN5_UnitResponse;
  Uni->Render = (VOID *)EN5_UnitRender;
  Uni->Close = (VOID *)EN5_UnitClose;
  return (en5UNIT *)Uni;
} /* End of 'EN5_UnitCreatePlane' function */

/* END OF 'U_PLANE.C' FILE */