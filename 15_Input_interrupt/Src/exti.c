#include "exti.h"

#define GPIOC_EN			(1U<<2)
#define SYSCFG_EN			(1U<<14)




void pc13_exti_init(void)
{
	//DISABLE GLOBAL INTERRUPTS
	__disable_irq();

	//ENABLE CLOCK ACESS FOR GPIOC (AHB1)
	RCC->AHB1ENR |= GPIOC_EN;

	//SET PC13 AS AN INPUT
	GPIOC->MODER &=~ (1U<<27);
	GPIOC->MODER &=~ (1U<<26);

	//ENABLE CLOCK ACCESS TO SYSCFG
	RCC->APB2ENR |= SYSCFG_EN;

	//SELECT PORTC FOR EXTI13
	SYSCFG->EXTICR[3] &=~ (1U<<4);
	SYSCFG->EXTICR[3] |=  (1U<<5);
	SYSCFG->EXTICR[3] &=~ (1U<<6);
	SYSCFG->EXTICR[3] &=~ (1U<<7);

	//UNMASK EXTI13
	EXTI->IMR |= (1U<<13);

	//SELECT FALLING EDGE TRIGGER
	EXTI->FTSR |= (1U<<13);

	//ENABLE THE EXTI LINE IN NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//ENABLE GLOBAL INTERRUPTS
	__enable_irq();
}
