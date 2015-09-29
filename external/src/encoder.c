///----------------------------------------------------------------------------------------
///
/// \file encoder.c
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

#include <driver/driver.h>

#if DRIVER_EXT_ENCODER

volatile ENCODER *encoders[16];

uint16_t encoder_create(ENCODER *encoder)
{
	uint8_t *port = PORT1;
	uint8_t pin = (1 << (encoder->int_number_A % 8));

	encoder->old_count = 0x8000;

	///>Configure PIN for signal A

	if(encoder->int_number_A >= 8){
		port = PORT2;
	}

	PIE(port) &= ~(pin);					//Disable Interrupt on all listed Pins
	PDIR(port) &= ~(pin);
	PREN(port) |= pin;
	POUT(port) |= (pin); //default &= ~

	if((PIN(port) & pin) != 0)
	{
		encoder->last = 3;											//Decode Graycode new = Bit1 := A and Bit0 := A^B
		PIES(port) |= pin;								//Interrupt for a falling edge for Signal A

	}

	encoders[encoder->int_number_A] = encoder;

	///>Configure PIN for signal B

	port = PORT1;
	pin = (1 << (encoder->int_number_A % 8));

	if(encoder->int_number_B >= 8){
		port = PORT2;
	}

	PIE(port) &= ~pin;					//Disable Interrupt on all listed Pins
	PDIR(port) &= ~pin;
	PREN(port) |= pin;
	POUT(port) |= (pin); //default &= ~

	if((PIN(port) & pin) != 0)
	{
		encoder->last ^= 1;										//Decode Graycode new = Bit1 := A and Bit0 := A^B
		PIES(port) |= pin;								//Interrupt for a falling edge for Signal B
	}

	encoders[encoder->int_number_B] = encoder;

	ext_interrupt_create(encoder->int_number_A, encoder_interrupt);
	ext_interrupt_create(encoder->int_number_B, encoder_interrupt);
	ext_interrupt_enable(encoder->int_number_A);
	ext_interrupt_enable(encoder->int_number_B);

	if(encoder->button.int_number_button != 0) {
		button_create(&(encoder->button), BUTTON_PULL_UP);
	}

	__bis_SR_register(GIE);
	return 0;
}

int16_t encoder_update(ENCODER *encoder)
{
							//Set a start Value in the Middle of Range
	uint16_t tmp_en = encoder->count;							//Save encoder_2_count if there is a break form a Interrupt
	uint16_t tmp_t = encoder->old_count/4;								//Calculate number of Steps
	uint16_t tmp_en_t = tmp_en/4;								//Calculate number of Steps
	if((tmp_en%4) == 3)												//Check if Encoder is near the next full Rast point
	{
		tmp_en_t++;													//if true up Value for Steps of act. Value
	}
	if((encoder->old_count%4) == 3)										//Check if last Value of Encoder was near the next full Rast point
	{
		tmp_t++;													//if true up Value for Steps of last Value
	}
	int16_t diff = tmp_en_t - tmp_t;									//make the difference of act. and last Value
	encoder->old_count = tmp_en;											//save act. Value as last Value
	encoder->steps += diff;
	return 0;													//give difference back
}

void encoder_interrupt(uint8_t int_number)
{
	int8_t encoder_new = 0, encoder_diff = 0;

	uint8_t *port = PORT1;
	uint8_t pin = (1 << (encoders[int_number]->int_number_A % 8));

	if(encoders[int_number]->int_number_A >= 8){
		port = PORT2;
	}

	if((PIN(port) & pin) != 0)							//Check Signal A for a High Value
	{
		encoder_new = 3;											//Decode Graycode new = Bit1 := A and Bit0 := A^B
	}

	PIES(port)^= (PIFG(port) & pin);

	port = PORT1;
	pin = (1 << (encoders[int_number]->int_number_B % 8));

	if(encoders[int_number]->int_number_A >= 8){
			port = PORT2;
	}

	if((PIN(port) & pin) != 0)							//Check Signal A for a High Value
	{
		encoder_new ^= 1;											//Decode Graycode new = Bit1 := A and Bit0 := A^B

	}
	encoder_diff = encoders[int_number]->last - encoder_new;				//The difference of last and new can only be -3, -1, 1, 3
	if(encoder_diff & 1 == 1)										//Check difference if an Error occurred. Bit0 is always 1
	{
		encoders[int_number]->last = encoder_new;								//Save the new Value form Encoder to last											//Rotary direction can be set to right(0) or left(1) this option only demand the count direction
		encoders[int_number]->count -= ((encoder_diff & 2) - 1);				//the difference is for right rotary 1 1 1 -3 and for left -1 -1 -1 3 the bit mask will force the second bit
	}

	PIES(port)^= (PIFG(port) & pin);
}

#endif /*DRIVER_EXT_ENCODER*/
