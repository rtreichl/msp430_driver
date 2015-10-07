///----------------------------------------------------------------------------------------
///
/// \file adc.h
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

#ifndef DRIVER_MSP430_INCLUDE_ADC_H_
#define DRIVER_MSP430_INCLUDE_ADC_H_

#include <driver/driver.h>

/// ADC reference voltages

#define ADC_REF_SRC_VCC_VSS			SREF_0
#define ADC_REF_SRC_VREF_VSS		SREF_1
#define ADC_REF_SRC_VEREF_VSS		SREF_2

/// ADC sampel and hold times

#define ADC_SH_4_CYCLES				ADC10SHT_0
#define ADC_SH_8_CYCLES				ADC10SHT_1
#define ADC_SH_16_CYCLES			ADC10SHT_2
#define ADC_SH_64_CYCLES			ADC10SHT_3

/// ADC clock dividers

#define ADC_CLOCK_DIVIDER_1			ADC10DIV_0
#define ADC_CLOCK_DIVIDER_2			ADC10DIV_1
#define ADC_CLOCK_DIVIDER_3			ADC10DIV_2
#define ADC_CLOCK_DIVIDER_4			ADC10DIV_3
#define ADC_CLOCK_DIVIDER_5			ADC10DIV_4
#define ADC_CLOCK_DIVIDER_6			ADC10DIV_5
#define ADC_CLOCK_DIVIDER_7			ADC10DIV_6
#define ADC_CLOCK_DIVIDER_8			ADC10DIV_7

/// ADC clock sources

#define ADC_CLOCK_SRC_ADC_OSC		ADC10SSEL_0
#define ADC_CLOCK_SRC_ACLK			ADC10SSEL_1
#define ADC_CLOCK_SRC_MCLK			ADC10SSEL_2
#define ADC_CLOCK_SRC_SMCLK			ADC10SSEL_3

/// ADC internal reference voltages

#define ADC_REF_VOLTAGE_2_5V		(REF2_5V & REF_ON)
#define ADC_REF_VOLTAGE_1_5V		REF_ON

/// ADC buffer configurations

#define ADC_REF_BUFFER_200KBPS		0
#define ADC_REF_BUFFER_50KBPS		ADC10SR
#define ADC_REF_BUFFER_CONT_ON		0
#define ADC_REF_BUFFER_ONLY_ON_SH	REFBURST

/// ADC sample and hold soucres

#define ADC_SH_SOURCE_ADC_OSC		SHS_0
#define ADC_SH_SOURCE_TIMERA_OUT1	SHS_1
#define ADC_SH_SOURCE_TIMERA_OUT0	SHS_2
#define ADC_SH_SOURCE_TIMERA_OUT2	SHS_3

/// ADC data output formate

#define ADC_DATA_NORMAL_BINARY		0
#define ADC_DATA_2S_COMPLEMTARY		ADC10DF

/// ADC working modes all modes are in sequence

#define ADC_CONVERSION_SINGLE		CONSEQ_1
#define ADC_CONVERSION_REPEATED		CONSEQ_3

/// ADC build configuration. Pleas edit here configuration for build

#define ADC_CLOCK_SOURCE			ADC_CLOCK_SRC_MCLK
#define ADC_CLOCK_DIVIDER			ADC_CLOCK_DIVIDER_4
#define ADC_SAMPLE_HOLD_TIME		ADC_SH_8_CYCLES
#define ADC_REFERENCE_OUTPUT		DRIVER_FALSE
#define ADC_REFERENCE_SOURCE		ADC_REF_SRC_VCC_VSS
#define ADC_REFERENCE_INTERNAL		DRIVER_FALSE
#define ADC_REFERENCE_SAMPLE_RATE	DRIVER_FALSE
#define ADC_REFERENCE_BURST			DRIVER_FALSE
#define ADC_DATA_FORMAT				ADC_DATA_NORMAL_BINARY
#define ADC_SAMPLE_HOLD_SOURCE		ADC_SH_SOURCE_ADC_OSC
#define ADC_CONVERSION_MODE			ADC_CONVERSION_REPEATED

typedef struct {
	uint8_t port;
	uint16_t *result;
} ADC;

uint16_t adc_init(uint16_t *storage);
uint16_t adc_create(ADC *adc);
uint16_t adc_delete(ADC *adc);
uint16_t adc_busy();

#endif /* DRIVER_MSP430_INCLUDE_ADC_H_ */
