/* FILE NAME: IMAGE.H
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Image constract module.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "rndres.h"

typedef struct tagen5IMAGE
{
  INT W, H; /*Image size */
  BYTE *Pixels; /* Pixel array */
  DWORD *PixelsDW; /* Pixel array */
  BYTE (*PixelsC)[4]; /* Pixel array */
} en5IMAGE;

/* Create image maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 *   - size of image:
 *       INT W, H;
 * RETURNS:
 *  (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_ImgCreate( en5IMAGE *Im, INT W, INT H );

/* Load image in maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 *   - name of image:
 *       CHAR *FileName;
 * RETURNS:
 *  (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL EN5_ImgLoad( en5IMAGE *Im, CHAR *FileName );

/* Create image maket function.
 * ARGUMENTS:
 *   - pointer to image to create:
 *       en5IMAGE *Im;
 * RETURNS: None.
 */
VOID EN5_ImgFree( en5IMAGE *Im );

#endif /* __IMAGE_H_ */

/* END OF 'IMAGE.H' FILE */
