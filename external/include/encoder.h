///----------------------------------------------------------------------------------------
///
/// \file encoder.h
///
/// \brief
///
/// \date 25.09.2015
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

#ifndef ENCODER_H_
#define ENCODER_H_

#include <driver/driver.h>

#define TIME_FOR_LONG_PRESS 150
#define TIME_FOR_SHORT_PRESS 10

typedef struct {
	uint16_t count;
	uint16_t old_count;
	int8_t last;
	int8_t steps;
	uint8_t int_number_A;
	uint8_t int_number_B;
	BUTTON button;
} ENCODER;

int16_t encoder_update(ENCODER *encoder);
uint16_t encoder_create(ENCODER *encoder);
void encoder_interrupt(uint8_t int_number);

#endif /* ENCODER_H_ */
