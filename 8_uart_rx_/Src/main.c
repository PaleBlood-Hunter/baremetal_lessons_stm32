#include <stdint.h>
#include "stm32f4xx.h"

#include "uart.h"

#define GPIOAEN					(1U<<0)

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

char key;

int main(void)
{

	//1. ENABLE CLOCK ACCESS TO GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. SET PA5 AS AN OUTPUT
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);


	uart2_rxtx_init();

	while(1)
	{
		key = uart2_read();
		if(key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else if(key == '0')
		{
			GPIOA->ODR &=~ LED_PIN;
		}
	}
}


