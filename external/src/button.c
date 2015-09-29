///----------------------------------------------------------------------------------------
///
/// \file button.c
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

#include <driver/driver.h>

#if DRIVER_EXT_BUTTON

volatile BUTTON *buttons[16] = {0};
volatile uint16_t *button_timer = 0;

uint8_t button_init(uint16_t *timer)
{
	button_timer = timer;
	return 0;
}

uint16_t button_time_diff(uint16_t time_stamp, uint16_t time_actual)
{
	if(time_stamp > time_actual) {
		return 0xFFFF - (time_stamp - time_actual);
	}
	else {
		return time_actual - time_stamp;
	}
}

uint8_t button_create(BUTTON *button, uint8_t state)
{
	uint8_t *port = PORT1;
	uint8_t pin = (1 << (button->int_number_button % 8));

	button->time = 0;
	button->long_pressed = 0;
	button->short_pressed = 0;

	buttons[button->int_number_button] = button;

	if(button->int_number_button >= 8) {
		port = PORT2;
	}

	if(state == BUTTON_PULL_UP) {
		PREN(port) |= pin;   // force high
		POUT(port) |= pin;
		PIES(port) |= pin; // for rising edge
	}
	else {
		PREN(port) |= pin;
		POUT(port) &= ~pin;  // for falling edge
		PIES(port) &= ~pin;
	}
	ext_interrupt_create(button->int_number_button, button_interrupt);
	ext_interrupt_enable(button->int_number_button);
	return 0;
}

uint8_t button_get(uint8_t int_number)
{
	if(button_time_diff(buttons[int_number]->time, *button_timer) > BUTTON_PRESS_LONG) {
		buttons[int_number]->long_pressed--;
		return 1;
	}
//	button->long_pressed  += button_pressed_long[int_number];
//	button->short_pressed += button_pressed_short[int_number];
//	button_pressed_short[int_number] = 0;
//	button_pressed_long[int_number]= 0;
	return 0;
}

void button_interrupt(uint8_t int_number)
{
	uint8_t *port = PORT1;
	uint8_t pin = (1 << (buttons[int_number]->int_number_button % 8));

	if(int_number >= 8) {
		port = PORT2;
	}

	if(buttons[int_number]->time == 0) {
		buttons[int_number]->time = *button_timer;
	}
	else {
		buttons[int_number]->time = button_time_diff(buttons[int_number]->time, *button_timer);
		if(buttons[int_number]->time > BUTTON_PRESS_LONG) {
			buttons[int_number]->long_pressed++;
			buttons[int_number]->time = 0;
		}
		else if(buttons[int_number]->time > BUTTON_PRESS_SHORT){
			buttons[int_number]->short_pressed++;
			buttons[int_number]->time = 0;
		}
	}
	PIES(port) ^= pin;
}

#endif /*DRIVER_BUTTON_H_*/
