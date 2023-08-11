#include "stm32f4xx.h"
#include "adc.h"

#define ADC1EN		(1U<<8)
#define GPIOAEN		(1U<<0)

#define ADC_CH1		(1U<<0)
#define CR2_ADON	(1U<<0)

#define CR2_SWSTART	(1U<<30)
#define SR_EOC		(1U<<1)


void pa1_ac_init(void)
{
	//**********************************
	//***CONFIGURE THE ADC GPIO PINS:***
	//**********************************

	//ENABLE CLOCK ACCESS TO GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//CONFIGURE PA1 PIN AS ADC1
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//**********************************
	//***CONFIGURE THE ADC MODULE:***
	//**********************************

	//ENABLE CLOCK ACCESS TO ADC1
	RCC->APB2ENR |= ADC1EN;

	//CONVERSION SEQUENCE START
	ADC1->SQR3 = ADC_CH1;

	//CONVERSION SEQUENCE LENGTH
	ADC1->SQR1 = 0x00;

	//ENABLE ADC MODULE
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void)
{
	//START ADC CONVERSION
	ADC1->CR2 |= CR2_SWSTART;
}


uint32_t adc_read(void)
{
	//WAIT CONVERSION TO BE COMPLETE
	while(!(ADC1->SR & SR_EOC));

	//READ CONVERTED RESULT
	return (ADC1->DR);
}
