/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsyscon.h - Interface to sceSysreg_driver.
 *
 * Copyright (c) 2006 James F
 *
 * $Id: pspsyscon.h 2152 2007-01-27 10:09:15Z tyranid $
 */

#ifndef PSPSYSCON_H
#define PSPSYSCON_H

#include <pspkerneltypes.h>

/** @defgroup Syscon Interface to the sceSyscon_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Syscon Interface to the sceSyscon_driver library. */
/*@{*/

/**
  * Force the PSP to go into standby
  */
void sceSysconPowerStandby(void);

/**
 * Reset the PSP
 *
 * @param unk1 - Unknown, pass 1
 * @param unk2 - Unknown, pass 1
 */
void sceSysconResetDevice(int unk1, int unk2);

#define SCE_LED_POWER 1
#define LED_ON 1
#define LED_OFF 0
/**
 * Control an LED
 *
 * @param SceLED - The led to toggle (only SCE_LED_POWER)
 * @param state - Whether to turn on or off
 */
int sceSysconCtrlLED(int SceLED, int state);

/**
 * Control the remote control power
 *
 * @param power - 1 is on, 0 is off
 * 
 * @return < 0 on error
 */
int sceSysconCtrlHRPower(int power);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
