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


int main(void)
{
	uart2_rxtx_init();
	tim2_1hz_interrupt_init();

	//1. ENABLE CLOCK ACCESS TO GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. SET PA5 AS AN OUTPUT
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	while(1)
	{


	}
}

static void tim2_callback(void)
{
	//6.TOGGLE PA5
	printf("A second has passed \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void TIM2_IRQHandler(void)
{
	//CLEAR THE UPDATE INTERRUPT FLAG
	TIM2->SR &=~ SR_UIF;

	//DO SOMETHING
	tim2_callback();
}
