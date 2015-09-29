///----------------------------------------------------------------------------------------
///
/// \file msp430_advanced.h
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

#ifndef DRIVER_MSP430_INCLUDE_MSP430_ADVANCED_H_
#define DRIVER_MSP430_INCLUDE_MSP430_ADVANCED_H_

#include <msp430.h>
#include <stdint.h>

#define PORT1 (uint8_t *) &P1IN
#define PORT2 (uint8_t *) &P2IN

#define PIN(PORT)	*(PORT+0)
#define POUT(PORT)	*(PORT+1)
#define	PDIR(PORT)	*(PORT+2)
#define PIFG(PORT)	*(PORT+3)
#define PIES(PORT)	*(PORT+4)
#define PIE(PORT)	*(PORT+5)
#define PSEL(PORT)	*(PORT+6)
#define PREN(PORT)	*(PORT+7)

#endif /* DRIVER_MSP430_INCLUDE_MSP430_ADVANCED_H_ */
