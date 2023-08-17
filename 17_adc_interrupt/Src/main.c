#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

#define GPIOAEN					(1U<<0)


#define PIN5					(1U<<5)
#define LED_PIN					PIN5

char key;
uint32_t sensor_value = 0;

static void adc_callback(void);

int main(void)
{
	uart2_rxtx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1)
	{

	}
}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor value : %d \n\r",(int)sensor_value);
}


void ADC_IRQHandler(void)
{
	//CHECK FOR EOC FLAG IN SR
	if((ADC1->SR & SR_EOC) != 0)
	{
		//CLEAR EOC FLAG IN SR
		ADC1->SR &=~ SR_EOC;

		//DO SOMETHING
		adc_callback();
	}
}
