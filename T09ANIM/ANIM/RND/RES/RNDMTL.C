/* FILE NAME: RNDMTL.C
 * PROGRAMMER: EN5
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Material module.
 */
#include "rndres.h"

en5MATERIAL EN5_RndMaterials[EN5_MAX_MATERIALS]; /* Array of materials */
INT EN5_RndMaterialsSize = 0;                    /* Materials array store size */

/* Initialization default matereal struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndMtlInit( VOID )
{
  INT i;

  strncpy(EN5_RndMaterials[0].Name, "MATERIALA", EN5_STR_MAX - 1);
  EN5_RndMaterials[0].Ka = VecSet1(0);
  EN5_RndMaterials[0].Kd = VecSet1(0.1);
  EN5_RndMaterials[0].Ks = VecSet1(0.2);
  EN5_RndMaterials[0].Ph = 100;
  EN5_RndMaterials[0].ShdNo = EN5_RndShaderAdd("DEFAULT");
  EN5_RndMaterials[0].Tex[0] = -1;
  for (i = 1; i < 8; i++)
    EN5_RndMaterials[0].Tex[i] = -1;
  EN5_RndMaterials[0].Trans = 0;
  EN5_RndMaterialsSize++;
} /* End of 'EN5_RndMtlInit' function */

/* Deinitialization matereal struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_RndMtlClose( VOID )
{
  INT i;

  for (i = 0; i < EN5_RndMaterialsSize; i++)
    memset(&EN5_RndMaterials[i], 0, sizeof(en5MATERIAL));
} /* End of 'EN5_RndMtlClose' function */

INT EN5_RndMtlAdd( en5MATERIAL *Mtl )
{
  CHAR tname[EN5_STR_MAX];
  INT i;

  if (EN5_RndMaterialsSize >= EN5_MAX_MATERIALS)
    return 0;

  strncpy(tname, EN5_RndMaterials[EN5_RndMaterialsSize - 1].Name, EN5_STR_MAX - 1);
  tname[8] = tname[8] + 1;
  strncpy(EN5_RndMaterials[EN5_RndMaterialsSize].Name, tname, EN5_STR_MAX - 1);
  EN5_RndMaterials[EN5_RndMaterialsSize].Ka = Mtl->Ka;
  EN5_RndMaterials[EN5_RndMaterialsSize].Kd = Mtl->Kd;
  EN5_RndMaterials[EN5_RndMaterialsSize].Ks = Mtl->Ks;
  EN5_RndMaterials[EN5_RndMaterialsSize].Ph = Mtl->Ph;
  EN5_RndMaterials[EN5_RndMaterialsSize].ShdNo = Mtl->ShdNo;
  EN5_RndMaterials[EN5_RndMaterialsSize].Trans = Mtl->Trans;

  for (i = 0; i < 8; i++)
    EN5_RndMaterials[EN5_RndMaterialsSize].Tex[i] = Mtl->Tex[i];

  return EN5_RndMaterialsSize++;
}

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - number of material:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) shader program Id.
 */
INT EN5_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  en5MATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= EN5_RndMaterialsSize)
    MtlNo = 0;
  mtl = &EN5_RndMaterials[MtlNo];

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= EN5_RndShadersSize)
    prg = 0;
  prg = EN5_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, EN5_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, EN5_Anim.GlobalTime);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, EN5_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'EN5_RndMtlApply' function */


/* END OF 'RNDMTL.C' FILE */