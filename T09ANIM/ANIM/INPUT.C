/* FILE NAME  : INPUT.C
 * PROGRAMMER : EN5
 * LAST UPDATE: 09.06.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Iput system.
 */

#include "anim.h"

#define EN5_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

/* Initilizate keyboard function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID EN5_AnimKeyboardInit( VOID )
{

} /* End of 'EN5_AnimKeyboardInit' function */

/* Keyboard interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
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

/* Mouse interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
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

/* Joystick interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_AnimJoystickResponse( VOID )
{
  INT i;

  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          EN5_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          EN5_Anim.JButClick[i] = EN5_Anim.JBut[i] && !EN5_Anim.JButOld[i];
          EN5_Anim.JButOld[i] = EN5_Anim.JBut[i];
        }
        /* Axes */
        EN5_Anim.JX = EN5_GET_JOYSTIC_AXIS(X);
        EN5_Anim.JY = EN5_GET_JOYSTIC_AXIS(Y);
        EN5_Anim.JZ = EN5_GET_JOYSTIC_AXIS(Z);
        EN5_Anim.JR = EN5_GET_JOYSTIC_AXIS(R);
        /* Point of view */
        EN5_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
} /* End of 'EN5_AnimJoystickResponse' function */

/* END OF 'INPUT.C' FILE */