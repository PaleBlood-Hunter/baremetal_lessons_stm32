/*
 * Systick.c
 *
 *  Created on: Aug 5, 2023
 *      Author: vinicius.ferreira
 *
 */

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VALUE			16000
#define CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)



void SystickDelayMs(int delay)
{
	//*********************************************
	//*************CONFIGURE SYSTICK***************
	//*********************************************

	//RELOAD WITH NUMBER OF CLOCK PER MILISECOND
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	//CLEAR SYSTICK CURRENT VALUE REGISTER
	SysTick->VAL = 0;

	//ENABLE SYSTICK AND SELECT INTERNAL CLOCK SOURCE
	SysTick->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++)
	{
		//WAIT FOR COUNTFLAG TO BE SET
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0);
	}

	//DISABLE SYSTICK COUNTER
	SysTick->CTRL = 0;

}
