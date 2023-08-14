#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "Systick.h"

#define GPIOAEN					(1U<<0)


#define PIN5					(1U<<5)
#define LED_PIN					PIN5

char key;
uint32_t sensor_value = 0;

int main(void)
{
	uart2_rxtx_init();


	//1. ENABLE CLOCK ACCESS TO GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. SET PA5 AS AN OUTPUT
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	while(1)
	{
		//4.TOGGLE PA5
		GPIOA->ODR ^= LED_PIN;

		printf("A second has passed \n\r");
		SystickDelayMs(1000);

	}
}


