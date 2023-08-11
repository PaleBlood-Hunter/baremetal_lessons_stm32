#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)
#define	LED_PIN			PIN5


int main(void)
{
	RCC->AHB1ENR |=GPIOAEN; //ENABLE THE CLOCK FOR PERIPHERAL A

	GPIOA->MODER |=(1U<<10); //SET PIN A5 AS AN OUTPUT
	GPIOA->MODER &=~(1U<<11);// THE SAME

	while(1)
	{
		GPIOA->ODR ^= LED_PIN;		//TOGGLE PIN 5
		for(int i=0;i<100000;i++);	//DELAY
	}
}


