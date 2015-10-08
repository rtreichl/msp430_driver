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

uint16_t adc_init(uint16_t *storage)
{
	ADC10CTL0 = ADC_REFERENCE_SOURCE |
				ADC_SAMPLE_HOLD_TIME |
				ADC_REFERENCE_SAMPLE_RATE |
				ADC_REFERENCE_OUTPUT |
				ADC_REFERENCE_BURST |
				MSC |
				ADC_REFERENCE_INTERNAL |
				ADC10ON |
				ADC10IE;


	ADC10CTL1 |= ADC_SAMPLE_HOLD_SOURCE |
				ADC_DATA_FORMAT |
				ADC_CLOCK_DIVIDER |
				ADC_CLOCK_SOURCE |
				ADC_CONVERSION_MODE;

	ADC10CTL1 |= (7 << 12);

	ADC10DTC1 = 8;

	ADC10SA = (uint16_t)storage; //should be enough for all 8 channels so far 8x16bit

	ADC10DTC0 = ADC10CT;

	ADC10CTL0 |= ENC |
				 ADC10SC;

	return 0;
}

uint16_t adc_create(ADC *adc)
{
	if(ADC10AE0 & (1 << adc->port)) {
		return 0; //TODO return Fault!!
	}

	adc->result = (uint16_t *)ADC10SA + 7 - adc->port; //reconfig pointer where result is stored from ADC

	ADC10AE0 |= (1 << adc->port);


	return 0;
}

uint16_t adc_delete(ADC *adc)
{
	if(!(ADC10AE0 & (1 << adc->port))) {
		return 0; //TODO return Fault!!
	}

	ADC10AE0 &= ~(1 << adc->port);
	return 0;
}

uint16_t adc_busy()
{
	return 0;
}

#pragma vector=ADC10_VECTOR
__interrupt void adc(void)
{

}


#endif /*DRIVER_MSP430_ADC*/
