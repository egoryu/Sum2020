/* FILE NAME: UNITS.H
 * PROGRAMMER: EN5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "../def.h"
#include "../anim/anim.h"

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateBall( VOID );

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (en5UNIT_CTRL *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateControl( VOID );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (en5UNIT *) pointer to created unit.
 */
en5UNIT * EN5_UnitCreateCow( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */