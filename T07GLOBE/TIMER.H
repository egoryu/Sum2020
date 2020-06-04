/* FILE NAME: TIMER.H
 * PROGRAMMER: EN5
 * DATE: 04.06.2020
 * PURPOSE: draw 3D object.
 */

#include <windows.h>

extern DOUBLE
  GlobalTime,
  GlobalDeltaTime,
  FPS;
extern BOOL
  IsPause;

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TimerInit( VOID );

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TimerResponse( VOID );

/* END OF 'TIMER.H' FILE */