///----------------------------------------------------------------------------------------
///
/// \file msp430.h
///
/// \brief 
///
/// \date 29.09.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#ifndef DRIVER_MSP430_MSP430_H_
#define DRIVER_MSP430_MSP430_H_

#include "include/msp430_advanced.h"

#if DRIVER_MSP430_EXT
#include "include/external_interrupthandler.h"
#endif

#if DRIVER_MSP430_FLASH
#include "include/flash.h"
#endif

#if DRIVER_MSP430_I2C
#include "include/i2c.h"
#endif

#if DRIVER_MSP430_TIMER
#include "include/timer.h"
#endif

#if DRIVER_MSP430_ADC
#include "include/adc.h"
#endif

#endif /* DRIVER_MSP430_MSP430_H_ */
