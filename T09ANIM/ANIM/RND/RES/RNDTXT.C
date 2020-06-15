/* FILE NAME: RNDTXT.C
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Textures module.
 */
#include <stdio.h>

#include "rndres.h"

en5TEXTURE EN5_RndTextures[EN5_MAX_TEXTURES]; /* Array of textures */
INT EN5_RndTexturesSize = 0;                  /* Textures array store size */

/* Initialization texture struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndTexInit( VOID )
{
  EN5_RndTexAddG24("P06.G24");
} /* End of 'EN5_RndTexInit' function */

/* Deinitialization texture struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < EN5_RndTexturesSize; i++)
    glDeleteTextures(1, &EN5_RndTextures[i].TexId);
  EN5_RndTexturesSize = 0;
} /* End of 'EN5_RndTexClose' function */

/* Add texture from image function.
 * ARGUMENTS:
 *   - Name of texture:
 *       CHAR *Name;
 *   - size of texture:
 *       INT W, H;
 *   - point array of component:
 *       DWORD *Bits;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT EN5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, BYTE *Bits )
{
  if (EN5_RndTexturesSize >= EN5_MAX_TEXTURES)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &EN5_RndTextures[EN5_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, EN5_RndTextures[EN5_RndTexturesSize].TexId);

  /* Upload texture */
  gluBuild2DMipmaps(GL_TEXTURE_2D, C, W, H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Bits);
  glTexImage2D(GL_TEXTURE_2D, 0, C, W, H, 0,
    C == 3 ? GL_BGR : C == 4 ? GL_BGRA : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(EN5_RndTextures[EN5_RndTexturesSize].Name, Name, EN5_STR_MAX - 1);
  EN5_RndTextures[EN5_RndTexturesSize].W = W;
  EN5_RndTextures[EN5_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return EN5_RndTexturesSize++;
} /* End of 'EN5_RndTexAddImg' function */

/* Add texture from file G24 function.
 * ARGUMENTS:
 *   - Name of file:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT EN5_RndTexAddG24( CHAR *FileName )
{
  BYTE *img;
  INT w = 0, h = 0;
  FILE *F;

  if (EN5_RndTexturesSize >= EN5_MAX_TEXTURES)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &EN5_RndTextures[EN5_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, EN5_RndTextures[EN5_RndTexturesSize].TexId);

  if ((F = fopen(FileName, "rb")) == NULL)
    return -1;

  fread(&w, 2, 1, F);
  fread(&h, 2, 1, F);

  if ((img = malloc(3 * w * h)) == NULL)
  {
    fclose(F);
    return -1;
  }

  fread(img, 3, w * h, F);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* Upload texture */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, img);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(EN5_RndTextures[EN5_RndTexturesSize].Name, FileName, EN5_STR_MAX - 1);
  EN5_RndTextures[EN5_RndTexturesSize].W = w;
  EN5_RndTextures[EN5_RndTexturesSize].H = h;

  glBindTexture(GL_TEXTURE_2D, 0);

  free(img);
  fclose(F);

  return EN5_RndTexturesSize++;
} /* End of 'EN5_RndTexAddG24' function */

/* Add texture from file BMP function.
 * ARGUMENTS:
 *   - Name of file:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT EN5_RndTexAddBMP( CHAR *FileName )
{
  en5IMAGE img;

  if (EN5_RndTexturesSize >= EN5_MAX_TEXTURES)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &EN5_RndTextures[EN5_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, EN5_RndTextures[EN5_RndTexturesSize].TexId);

  if ((EN5_ImgLoad(&img, FileName)) == FALSE)
    return -1;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* Upload texture */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.W, img.H, GL_BGRA, GL_UNSIGNED_BYTE, img.Pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(EN5_RndTextures[EN5_RndTexturesSize].Name, FileName, EN5_STR_MAX - 1);
  EN5_RndTextures[EN5_RndTexturesSize].W = img.W;
  EN5_RndTextures[EN5_RndTexturesSize].H = img.H;

  glBindTexture(GL_TEXTURE_2D, 0);

  EN5_ImgFree(&img);
  return EN5_RndTexturesSize++;
} /* End of 'EN5_RndTexBMP' function */

/* END OF 'RNDTXT.C' FILE */