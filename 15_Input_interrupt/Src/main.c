#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "Systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN					(1U<<0)


#define PIN5					(1U<<5)
#define LED_PIN					PIN5

static void exti_callback(void);

int main(void)
{
	pc13_exti_init();

	uart2_rxtx_init();

	//1. ENABLE CLOCK ACCESS TO GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. SET PA5 AS AN OUTPUT
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	while(1)
	{

	}
}


//create the callback function
static void exti_callback(void)
{
	printf("BTN Pressed...\n\r");
	GPIOA->ODR ^= LED_PIN;
}


//IMPLEMENT THE INTERRUPT HANDLER
void EXTI15_10_IRQHandler(void) {
	if((EXTI->PR & LINE13) != 0)
	{
		//CLEAR THE PR FLAG
		EXTI->PR |= LINE13;

		//DO SOMETHING
		exti_callback();
	}
}

