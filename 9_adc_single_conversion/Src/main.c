#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

#define GPIOAEN					(1U<<0)


#define PIN5					(1U<<5)
#define LED_PIN					PIN5

char key;
uint32_t sensor_value = 0;

int main(void)
{
	uart2_rxtx_init();
	pa1_ac_init();

	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor value : %d \n\r",(int)sensor_value);

		for(int i=0;i<100000;i++);
	}
}


