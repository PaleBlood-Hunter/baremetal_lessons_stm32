#include "stm32f4xx.h"
#include "tim.h"

#define TIM2EN_CLK			(1U<<0)
#define CR1_CEN				(1U<<0)

void tim2_1hz_init(void)
{
	//ENABLE CLOCK ACCESS TO APB1
	RCC->APB1ENR |= TIM2EN_CLK;

	//SET THE PRESCALER VALUE
	TIM2->PSC = 1600 - 1; // 16MHz/1600Hz

	//SET THE AUTORELOAD VALUE
	TIM2->ARR = 10000 - 1;

	//CLEAR COUNTER
	TIM2->CNT = 0x00;

	//ENABLE TIMER
	TIM2->CR1 |= CR1_CEN;
}
