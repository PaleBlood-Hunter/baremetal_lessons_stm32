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


	uart2_rxtx_interrupt_init();

	while(1)
	{

	}

}

static void usart2_callback(void)
{
	key = USART2->DR;

	if(key == '1')
	{
		GPIOA->ODR |= LED_PIN;
	}
	else
	{
		GPIOA->ODR &=~ LED_PIN;
	}
}

void USART2_IRQHandler(void)
{
	//CHECK IF RXNE IS SET
	if(USART2->SR & SR_RXNE)
	{
		//DO SOMETHING
		usart2_callback();
	}
}

