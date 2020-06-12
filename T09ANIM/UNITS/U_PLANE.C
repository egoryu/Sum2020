/* FILE NAME: U_PLANE.C
 * PROGRAMMER: EN5
 * DATE: 12.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "units.h"

#define GRID_H 1024
#define GRID_W 1024

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
  static HBITMAP hBm, hBm1;
  static BYTE *Pixels, *Pixels1;
  static BITMAP bm, bm1;
  static en5VERTEX V[GRID_H][GRID_W];
  INT b, g, r, x, y, b1, g1, r1;

  hBm = LoadImage(NULL, "hftex.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
  hBm1 = LoadImage(NULL, "hf.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
  GetObject(hBm, sizeof(bm), &bm);
  GetObject(hBm1, sizeof(bm1), &bm1);

  Pixels = bm.bmBits;
  Pixels1 = bm1.bmBits;
  for (y = 0; y < GRID_H; y++)
    for (x = 0; x < GRID_W - 2; x++)
    {
      b = Pixels[bm.bmWidthBytes * y + x * (bm.bmBitsPixel / 8) + 0];
      g = Pixels[bm.bmWidthBytes * y + x * (bm.bmBitsPixel / 8) + 1];
      r = Pixels[bm.bmWidthBytes * y + x * (bm.bmBitsPixel / 8) + 2];
      
      b1 = Pixels1[bm1.bmWidthBytes * y + x * (bm1.bmBitsPixel / 8) + 0];
      g1 = Pixels1[bm1.bmWidthBytes * y + x * (bm1.bmBitsPixel / 8) + 1];
      r1 = Pixels1[bm1.bmWidthBytes * y + x * (bm1.bmBitsPixel / 8) + 2];

      V[y][x].P = VecSet(x - GRID_W / 2, (b1 + g1 + r1), GRID_H / 2 - y);
      V[y][x].C = Vec4Set(r / 255.0, g / 255.0, b / 255.0, 1);
    }
  EN5_RndPrimCreateFromGrid(&Uni->Plane, V[0], GRID_W, GRID_H, TRUE);
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