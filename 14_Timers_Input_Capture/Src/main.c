#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "Systick.h"
#include "tim.h"

#define GPIOAEN					(1U<<0)


#define PIN5					(1U<<5)
#define LED_PIN					PIN5

int timestamp = 0;

//CONNECT A JUMPER FROM PA5 TO PA6
int main(void)
{
	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while(1)
	{
		//WAIT UNTIL EDGE IS CAPTURED
		while(!(TIM3->SR & SR_CC1IF)){}

		//READ VALUE
		timestamp = TIM3->CCR1;
	}
}
