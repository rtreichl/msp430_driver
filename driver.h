/*
 * driver.h
 *
 *  Created on: 26.05.2015
 *      Author: Richard
 */

#ifndef DRIVER_DRIVER_H_
#define DRIVER_DRIVER_H_

#define DRIVER_ENABLE	1
#define DRIVER_DISABLE	0

#define DRIVER_MSP430_I2C	DRIVER_ENABLE
#define DRIVER_MSP430_EXT	DRIVER_ENABLE
#define DRIVER_MSP430_FLASH	DRIVER_DISABLE
#define DRIVER_MSP430_TIMER	DRIVER_ENABLE

#include "msp430/msp430.h"

#define DRIVER_EXT_SI4735	DRIVER_ENABLE
#define DRIVER_EXT_BUTTON	DRIVER_ENABLE
#define DRIVER_EXT_ENCODER	DRIVER_ENABLE

#include "external/external.h"

#endif /* DRIVER_DRIVER_H_ */
