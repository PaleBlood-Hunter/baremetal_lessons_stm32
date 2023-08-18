#include "uart.h"

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)

#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)


#define CR1_RXNEIE		(1U<<5)


#define DMA1EN			(1U<<21)
#define CHSEL4						(1U<<27)
#define DMA_MEM_INC					(1U<<10)
#define DMA_DIR_MEM_TO_PERIPH		(1U<<6)
#define DMA_CR_TCIE				    (1U<<4)
#define DMA_CR_EN				     (1U<<0)
#define UART_CR3_DMAT				 (1U<<7)
#define DMA_CFEIF6		(1U<<16)
#define DMA_CDMEIF6		(1U<<18)
#define DMA_CTEIF6		(1U<<19)
#define DMA_CHTIF6		(1U<<20)
#define DMA_CTCIF6		(1U<<21)



#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE		115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
	//ENABLE CLOCK ACCESS TO THE DMA
	RCC->AHB1ENR |= DMA1EN;

	//DISABLE DMA1 STREAM 6
	DMA1_Stream6->CR &=~ DMA_CR_EN;

	//CLEAR ALL INTERRUPTS FLAGS OF STREAM 6
	DMA1->HIFCR |= DMA_CFEIF6;
	DMA1->HIFCR |= DMA_CDMEIF6;
	DMA1->HIFCR |= DMA_CTEIF6;
	DMA1->HIFCR |= DMA_CHTIF6;
	DMA1->HIFCR |= DMA_CTCIF6;

	//SET THE DESTINATION BUFFER
	DMA1_Stream6->PAR = dst;

	//SET THE SOURCE BUFFER
	DMA1_Stream6->M0AR = src;

	//SET THE LENGTH
	DMA1_Stream6->NDTR = len;

	//SELECT THE STREAM (STREAM6, CHANNEL4) AS IN THE REQUEST MAPPING
	DMA1_Stream6->CR = CHSEL4;

	//ENABLE MEMORY INCREMENT
	DMA1_Stream6->CR |= DMA_MEM_INC;

	//CONFIGURE THE TRANSFER DIRECTION
	DMA1_Stream6->CR |= DMA_DIR_MEM_TO_PERIPH;

	/*Enable DMA transfer complete interrupt*/
	DMA1_Stream6->CR |=DMA_CR_TCIE;

	//SET DIRECTION TO MEMORY TO PERIPHERAL (BECAUSE IS TX)
	DMA1_Stream6->FCR = 0;

	//ENABLE DIRECT MODE AND DISABLE FIFO
	DMA1_Stream6->FCR = 0;

	//ENABLE DMA1 STREAM6
	DMA1_Stream6->CR |=DMA_CR_EN;

	//ENABLE USART2 TRANSMITTER DMA
	USART2->CR3 |=UART_CR3_DMAT;

	//DMA INTERRUPT ENABLEIN NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

void uart2_rxtx_interrupt_init(void)
{
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	//SET PA3 MODE TO ALTERNATE FUNCTION MODE
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	//SET PA3 ALTERNATE FUNCTION TYPE TO UART_TX (AF07)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	 //ENABLE RXNE INTERRUPT
	 USART2->CR1 |= CR1_RXNEIE;

	 //ENABLE UART2 INTERRUPT IN NVIC
	 NVIC_EnableIRQ(USART2_IRQn);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;


}


void uart2_write(int ch)
{
  /*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE)){}

  /*Write to transmit data register*/
	USART2->DR	=  (ch & 0xFF);
}

char uart2_read(void)
{
	/*Make sure the receive data register is not empty*/
	while(!(USART2->SR & SR_RXNE)){}

	/*Read receive data register*/
	return USART2->DR;
}



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}


