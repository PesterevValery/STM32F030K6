#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "max6675.h"
#include "segled.h"
#include "systimer.h"

tact frq;
segled indicator (segled::A, segled::A);

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;

extern "C"
{
	void SysTick_Handler ();
}


void SysTick_Handler ()
{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
}


int main()
{
  max6675 sensor;
  systimer (systimer::ms, 1);
  
  while (1)
  {
		indicator.get_buffer (sensor.readCelsius());
		delay_ms (500);
  }
}

