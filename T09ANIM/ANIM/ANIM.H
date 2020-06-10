/* FILE NAME: ANIM.H
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "../def.h"
#include "RND/rnd.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm")

#define EN5_MAX_UNITS 1000
#define UNIT_BASE_FIELDS \
  VOID (*Init)( en5UNIT *Uni, en5ANIM *Ani );      \
  VOID (*Close)( en5UNIT *Uni, en5ANIM *Ani );     \
  VOID (*Response)( en5UNIT *Uni, en5ANIM *Ani );  \
  VOID (*Render)( en5UNIT *Uni, en5ANIM *Ani )

typedef struct tagen5UNIT en5UNIT;
typedef struct tagen5ANIM en5ANIM;
struct tagen5UNIT
{
  UNIT_BASE_FIELDS;
};
/* Animation context representation type */
struct tagen5ANIM
{
  /* Window data */
  HWND hWnd;                     /* Work window handle */
  HDC hDC;                       /* Back buffer context */
  INT W, H;                      /* Back buffer size */

  /* Units array data */
  en5UNIT *Units[EN5_MAX_UNITS]; /* Animation units array */
  INT NumOfUnits;                /* Animation units array size */

  /* Timer handle data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  /* Keyboard handle data */
  BYTE
    Keys[256],                   /* Keyboard state (true if key pressed) */
    KeysOld[256],                /* Previous frame keyboard state */
    KeysClick[256];              /* Key 'one-click' info */

  /* Mouse handle data */
  INT
    Mx, My, Mz,                  /* Absolute mouse coordinates */
    Mdx, Mdy, Mdz;               /* Relative mouse coordinates */

  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */
};

extern en5ANIM EN5_Anim;
extern INT EN5_MouseWheel;

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID EN5_AnimResize( INT W, INT H );

/* Copy frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_AnimCopyFrame( VOID );

/* Add unit function.
 * ARGUMENTS:
 *   - unit:
 *       en5UNIT *Uni.
 * RETURNS: None.
 */
VOID EN5_AnimUnitAdd( en5UNIT *Uni );

/* Initilizate animation function.
 * ARGUMENTS:
 *   - window handel:
 *       HWND hWnd.
 * RETURNS: None.
 */
VOID EN5_AnimInit( HWND hWnd );

/* Animation system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID EN5_AnimClose( VOID );

/* Animation system render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_AnimRender( VOID );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_AnimUnitCreate( INT Size );

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_TimerInit( VOID );

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_TimerResponse( VOID );

/* Turn full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_FlipFullScreen( VOID );

VOID EN5_AnimKeyboardResponse( VOID );
VOID EN5_AnimMouseResponse( VOID );
#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */