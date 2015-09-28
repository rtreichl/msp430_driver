///----------------------------------------------------------------------------------------
///
/// \file button.h
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

#ifndef DRIVER_BUTTON_H_
#define DRIVER_BUTTON_H_

#include <stdint.h>
#include <driver/external_interrupthandler.h>

#define BUTTON_PRESS_LONG 1500
#define BUTTON_PRESS_SHORT 50
#define BUTTON_PULL_DOWN 0xA0
#define BUTTON_PULL_UP	 0x0A

typedef struct {
	uint8_t short_pressed;
	uint8_t long_pressed;
} BUTTON;

uint8_t button_init(uint16_t *timer);
uint8_t button_create(uint8_t int_number, uint8_t state);
uint8_t button_hold_long(uint8_t int_number);

void button_interrupt(uint8_t int_number);

#endif /* DRIVER_BUTTON_H_ */
