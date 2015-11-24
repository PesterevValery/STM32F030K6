#include "segled.h"

char segled::number [11] = {0x7B , 0x0A , 0xB3 , 0x9F , 0xCA , 0xD9 , 0xF9 , 0x0B , 0xFB , 0xDB , 0x00};
char pins[4] = {segled::first, segled::second, segled::third, segled::fourth};

segled::segled (Port seg, Port dig)
:pin_segment (seg), pin_digit (dig)
{
	//===Settings segment pins===//
	pin_segment.setOutPin (a);
	pin_segment.setOutPin (b);	
	pin_segment.setOutPin (c);
	pin_segment.setOutPin (d);		
	pin_segment.setOutPin (e);
	pin_segment.setOutPin (f);	
	pin_segment.setOutPin (g);
	pin_segment.setOutPin (dp);		
	
	//===Settings digit pins===//
	pin_digit.setOutPin (first);
	pin_digit.setOutPin (second);	
	pin_digit.setOutPin (third);
	pin_digit.setOutPin (fourth);		
	

}

void segled::OFF ()
{
	pin_digit.clearPin (first);
	pin_digit.clearPin (second);	
	pin_digit.clearPin (third);
	pin_digit.clearPin (fourth);		
}

void segled::frame (uint8_t dig)
{
	pin_digit.clearPin (first);
	pin_digit.clearPin (second);
	pin_digit.clearPin (third);
	pin_digit.clearPin (fourth);
	pin_segment.setValPort (0);
	pin_digit.setPin (1 << pins[dig]);
	pin_segment.setValPort (number[buffer[dig]]);
}

void segled::digit ()
{
	static uint8_t i=0;
	frame (i);
	++i;
	if (i>=n)i=0;
}
/*
void segled::digit ()
{
	static uint8_t i=0;
	TIM14->SR &= ~TIM_SR_UIF;
	if (flag) flag = false;
		else
	{
		frame (i);
		flag = 1;
		++i;
	}
	if (i>=n)i=0;
}
*/
void segled::get_buffer (uint16_t val)
{
	char tous, hundr, dec, ones;
	uint16_t temp = val;

	for (tous=0;temp>=1000;++tous)temp -=1000;

	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;

	if (tous)
	{	
		buffer[3] = tous;
		buffer[2] = hundr;
		buffer[1] = dec;
		buffer[0] = ones;
		n=4;
	}
	else if (!(tous || hundr))
	{
		buffer[1] = dec;
		buffer[0] = ones;
		n=2;
	}
	else if (!(tous || hundr||dec))
	{
		buffer[0] = ones;
		n=1;
	}	
	else
	{
		buffer[2] = hundr;
		buffer[1] = dec;
		buffer[0] = ones;
		n=3;
	}
}