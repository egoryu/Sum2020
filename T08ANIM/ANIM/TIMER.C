/* FILE NAME  : TIMER.C
 * PROGRAMMER : EN5
 * LAST UPDATE: 08.01.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Timer implementation module.
 */

#include "anim.h"

/* Timer local data */
static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  EN5_Anim.IsPause = FALSE;
  EN5_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'EN5_TimerInit' function */

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EN5_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  EN5_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  EN5_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (EN5_Anim.IsPause)
  {
    EN5_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    EN5_Anim.DeltaTime = EN5_Anim.GlobalDeltaTime;
    EN5_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    EN5_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'EN5_TimerResponse' function */

/* END OF 'TIMER.C' FILE */
