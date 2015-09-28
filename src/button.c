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

#include <driver/button.h>

//volatile uint8_t button_pressed_short[16] = {0};
volatile BUTTON buttons[16] = {0};
volatile uint16_t button_time[16] = {0};
volatile uint16_t *button_timer = 0;

uint8_t button_init(uint16_t *timer)
{
	button_timer = timer;
	return 0;
}

uint16_t button_time_diff(uint16_t *time_stamp, uint16_t *time_actual)
{
	if(*time_stamp > *time_actual) {
		return 0xFFFF - (*time_stamp - *time_actual);
	}
	else {
		return *time_actual - *time_stamp;
	}
}

uint8_t button_create(uint8_t int_number, uint8_t state)
{
	uint8_t *pin_pointer = 0;

	if(int_number >= 8) {
		pin_pointer = (uint8_t *)&P2IN;
	}
	else {
		pin_pointer = (uint8_t *)&P1IN;
	}
	if(state == BUTTON_PULL_UP) {
		*(pin_pointer+7) |= (1 << (int_number % 8));   // force high
		*(pin_pointer+1) |= (1 << (int_number % 8));
		*(pin_pointer+4) |= (1 << (int_number % 8)); // for rising edge
	}
	else {
		*(pin_pointer+7)|= (1 << (int_number % 8));
		*(pin_pointer+1) &= ~(1 << (int_number % 8));  // for falling edge
		*(pin_pointer+4) &= ~(1 << (int_number %8));
	}
	ext_interrupt_create(int_number, button_interrupt);
	ext_interrupt_enable(int_number);
	return 0;
}

uint8_t button_get(uint8_t int_number)
{
	if(button_time_diff(button_time[int_number], button_timer) > BUTTON_PRESS_LONG) {
		buttons[int_number].long_pressed--;
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
	if(button_time[int_number] == 0) {
		button_time[int_number] = *button_timer;
	}
	else {
		button_time[int_number] = button_time_diff(button_time[int_number], button_timer);
		if(button_time[int_number] > BUTTON_PRESS_LONG) {
			buttons[int_number].long_pressed++;
			button_time[int_number] = 0;
		}
		else if(button_time[int_number] > BUTTON_PRESS_SHORT){
			buttons[int_number].short_pressed++;
			button_time[int_number] = 0;
		}
	}
	if(int_number >= 8) {
		P2IES ^= (1 << int_number);
	}
	else {
		P1IES ^= (1 << int_number);
	}
}
