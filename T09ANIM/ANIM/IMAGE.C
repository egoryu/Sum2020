/* FILE NAME: IMAGE.C
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Image constract module.
 */

#include "image.h"

/* Create image maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 *   - size of image:
 *       INT W, H;
 * RETURNS:
 *  (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_ImgCreate( en5IMAGE *Im, INT W, INT H )
{
  memset(Im, 0, sizeof(en5IMAGE));

  if ((Im->Pixels = malloc(W * H * 4)) == NULL)
    return FALSE;

  Im->H = H;
  Im->W = W;
  Im->PixelsDW = (DWORD *)Im->Pixels;
  Im->PixelsC = (BYTE (*)[4])Im->Pixels;

  return TRUE;
} /* End of 'EN5_ImgCreate' function */

/* Load image in maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 *   - name of image:
 *       CHAR *FileName;
 * RETURNS:
 *  (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_ImgLoad( en5IMAGE *Im, CHAR *FileName )
{
  HBITMAP hBm;
  BYTE *ptr;
  BITMAP bm;
  INT x, y, type, mulx[3] = {1, 3, 4}, rgb[3][3] = {{0, 0, 0}, {0, 1, 2}, {0, 1, 2}};

  memset(Im, 0, sizeof(en5IMAGE));

  if ((hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) == NULL)
    return FALSE;

  GetObject(hBm, sizeof(bm), &bm);

  EN5_ImgCreate(Im, bm.bmWidth, bm.bmHeight);

  if (bm.bmBitsPixel != 8 && bm.bmBitsPixel != 24 && bm.bmBitsPixel != 32)
  {
    DeleteObject(hBm);
    return FALSE;
  }

  type = bm.bmBitsPixel == 8 ? 0 : bm.bmBitsPixel == 24 ? 1 : 2;
  ptr = bm.bmBits;

  for (y = 0; y < Im->H; y++)
    for (x = 0; x < Im->W; x++)
    {
      BYTE
        b = ptr[bm.bmWidthBytes * y + x * mulx[type] + rgb[type][0]],
        g = ptr[bm.bmWidthBytes * y + x * mulx[type] + rgb[type][1]],
        r = ptr[bm.bmWidthBytes * y + x * mulx[type] + rgb[type][2]],
        a = 255;

      Im->Pixels[(y * Im->W + x) * 4 + 0] = b;
      Im->Pixels[(y * Im->W + x) * 4 + 1] = g;
      Im->Pixels[(y * Im->W + x) * 4 + 2] = r;
      Im->Pixels[(y * Im->W + x) * 4 + 3] = a;
    }

  DeleteObject(hBm);
  return TRUE;
} /* End of 'EN5_ImgLoad' function */

/* Create image maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 * RETURNS: None.
 */
VOID EN5_ImgFree( en5IMAGE *Im )
{
  free(Im->Pixels);
  memset(Im, 0, sizeof(en5IMAGE));
} /* End of 'EN5_ImgFree' function */

/* END OF 'IMAGE.C' FILE */