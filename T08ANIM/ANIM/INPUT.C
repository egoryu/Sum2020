/* FILE NAME  : INPUT.C
 * PROGRAMMER : EN5
 * LAST UPDATE: 09.06.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Iput system.
 */

#include "anim.h"

/* Initilizate keyboard function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID EN5_AnimKeyboardInit( VOID )
{

} /* End of 'EN5_AnimKeyboardInit' function */

VOID EN5_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(EN5_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    EN5_Anim.Keys[i] >>= 7;
    EN5_Anim.KeysClick[i] = EN5_Anim.Keys[i] && !EN5_Anim.KeysOld[i];
  }
  memcpy(EN5_Anim.KeysOld, EN5_Anim.Keys, 256);
}

/* Initilizate mouse function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID EN5_AnimMouseInit( VOID )
{

} /* End of 'EN5_AnimMouseInit' function */

VOID EN5_AnimMouseResponse( VOID )
{
  POINT pt;

  EN5_Anim.Mdz = EN5_MouseWheel;
  EN5_Anim.Mz += EN5_MouseWheel;
  EN5_MouseWheel = 0;

  GetCursorPos(&pt);
  ScreenToClient(EN5_Anim.hWnd, &pt);
  EN5_Anim.Mdx = pt.x - EN5_Anim.Mx;
  EN5_Anim.Mdy = pt.y - EN5_Anim.My;
  EN5_Anim.Mx = pt.x;
  EN5_Anim.My = pt.y;
}

/* Initilizate joystick function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID EN5_AnimJoystickInit( VOID )
{

} /* End of 'EN5_AnimJoystickInit' function */

static VOID EN5_AnimJoystickResponse( VOID )
{

}

/* END OF 'INPUT.C' FILE */