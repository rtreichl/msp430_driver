///----------------------------------------------------------------------------------------
///
/// \file adc.c
///
/// \brief 
///
/// \date 02.10.2015
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

#include <driver/driver.h>

#if DRIVER_MSP430_ADC

uint16_t adc_init()
{
	ADC10CTL0 |=	ADC10SHT1
	ADC10CTL1 |=
	ADC10AE0 |=
	//Only for MSP430F22xx
#ifdef ADC10AE1
			ADC10AE1 |=
#endif
	ADC10DTC0 |=
	ADC10DTC1 |=
	ADC10SA |=
	return 0;
}

#endif /*DRIVER_MSP430_ADC*/
