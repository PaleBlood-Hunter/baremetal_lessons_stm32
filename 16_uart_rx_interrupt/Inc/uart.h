/*
 * uart.h
 *
 *  Created on: Aug 2, 2023
 *      Author: vinicius.ferreira
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>

#define SR_RXNE			(1U<<5)

void uart2_rxtx_interrupt_init(void);
char uart2_read(void);


#endif /* UART_H_ */
