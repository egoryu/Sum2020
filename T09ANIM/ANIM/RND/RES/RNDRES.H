/* FILE NAME: RNDRES.H
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Resurses module.
 */

#ifndef __RNDRES_H_
#define __RNDRES_H_

#include "../../anim.h"
#include "image.h"

#define EN5_STR_MAX  300
#define EN5_MAX_TEXTURES 3000
#define EN5_MAX_SHADERS  47
#define EN5_MAX_MATERIALS 5000

/* Shader program store type */
typedef struct tagen5SHADER
{
  CHAR Name[EN5_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} en5SHADER;

extern en5SHADER EN5_RndShaders[EN5_MAX_SHADERS];
extern INT EN5_RndShadersSize;

/* Texture representation type */
typedef struct tagen5TEXTURE
{
  CHAR Name[EN5_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} en5TEXTURE;

extern en5TEXTURE EN5_RndTextures[EN5_MAX_TEXTURES]; /* Array of textures */
extern INT EN5_RndTexturesSize;                      /* Textures array store size */

/* Material store type */
typedef struct tagen5MATERIAL
{
  CHAR Name[EN5_STR_MAX]; /* Material name */

  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table (or -1) */

  INT ShdNo;                /* Shader number in shader array */
} en5MATERIAL;

extern en5MATERIAL EN5_RndMaterials[EN5_MAX_MATERIALS]; /* Array of materials */
extern INT EN5_RndMaterialsSize;                        /* Materials array store size */

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT EN5_RndShdLoad( CHAR *ShaderFileNamePrefix );

/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader number:
 *       INT ProgId;
 * RETURNS: None.
 */
VOID EN5_RndShdDelete( INT ShdNo );

/* Update all shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndShadersUpdate( VOID );

/* Add shader program function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) added shader table number.
 */
INT EN5_RndShaderAdd( CHAR *ShederFileNamePrefix );

/* Initialization texture struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndTexInit( VOID );

/* Deinitialization texture struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndTexClose( VOID );

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
INT EN5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, BYTE *Bits );

/* Add texture from file G24 function.
 * ARGUMENTS:
 *   - Name of file:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT EN5_RndTexAddG24( CHAR *FileName );

/* Add texture from file BMP function.
 * ARGUMENTS:
 *   - Name of file:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT EN5_RndTexAddBMP( CHAR *FileName );

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - number of material:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) shader program Id.
 */
INT EN5_RndMtlApply( INT MtlNo );

/* Initialization default matereal struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndMtlInit( VOID );

/* Deinitialization matereal struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndMtlClose( VOID );

/* Deinitialization resurse struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndResClose( VOID );

INT EN5_RndMtlAdd( en5MATERIAL *Mtl );

/* Initialization resurse struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndResInit( VOID );

/* Get material from context function.
 * ARGUMENTS:
 *   - number of material:
 *       INT MtlNo;
 * RETURNS:
 *   (en5MATERIAL *) material.
 */
en5MATERIAL * EN5_RndMtlGet( INT MtlNo );

/* Get default material from context function.
 * ARGUMENTS:
 *   - number of material:
 *       INT MtlNo;
 * RETURNS:
 *   (en5MATERIAL *) material.
 */
en5MATERIAL EN5_RndMtlGetDef( VOID );

#endif /* __RNDRES_H_ */

/* END OF 'RNDRES.H' FILE */