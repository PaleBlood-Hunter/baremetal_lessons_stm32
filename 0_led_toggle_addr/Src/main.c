 //Where is the led connected
//Port: A
//Pin: 5

//starting addr GPIOA 0x4002 0000 - ending addr 0x4002 03FF

#define PERIPH_BASE 			(0x40000000UL) //START ADDR FOR PERIPHERALS
#define AHB1PERIPH_OFFSET		(0x00020000UL) //START ADDR FOR PORT A
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET) //START ADDR PORT A
#define GPIOA_OFFSET			(0x0000UL) //START ADDR GPIOA

#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))


#define GPIOAEN					(1U<<0)

#define PIN5					(1U<<5)
#define LED_PIN					PIN5


int main(void)
{
	//1. ENABLE CLOCK ACCESS TO GPIOA
	RCC_AHB1EN_R |= GPIOAEN; 			//1U<<0  SET RCC CLOCK FOR GPIO A TO WORK
	//2. SET PA5 AS AN OUTPUT
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);
	while(1)
	{
		//3. SET PA5 HIGH
		//GPIOA_OD_R |= LED_PIN;

		//4.TOGGLE PA5
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0;i<100000;i++);
	}
}
