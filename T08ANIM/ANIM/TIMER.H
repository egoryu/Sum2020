/* FILE NAME: TIMER.H
 * PROGRAMMER: EN5
 * DATE: 04.06.2020
 * PURPOSE: draw 3D object.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "../def.h"

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

#endif /* __TIMER_H_ */

/* END OF 'TIMER.H' FILE */