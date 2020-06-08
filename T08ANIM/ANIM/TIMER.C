/* FILE NAME: TIMER.C
 * PROGRAMMER: EN5
 * DATE: 04.06.2020
 * PURPOSE: draw 3D object.
 */

#include <time.h>

#include "timer.h"

/* Timer global data */
DOUBLE
  GlobalTime,
  GlobalDeltaTime,
  FPS;
BOOL
  IsPause;

/* Timer local data */
static LONG
  StartTime,
  OldTime,
  PauseTime,
  OldFPSTime,
  FrameCount;

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TimerInit( VOID )
{
  StartTime = OldTime = OldFPSTime = clock();
  PauseTime = 0;
  FrameCount = 0;
  IsPause = FALSE;
} /* End of 'TimerInit' function */

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TimerResponse( VOID )
{
  LONG t = clock();

  if (!IsPause)
  {
    GlobalTime = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GlobalDeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GlobalDeltaTime = 0;
  }

  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
} /* End of 'TimerResponse' function */

/* END OF 'TIMER.C' FILE */