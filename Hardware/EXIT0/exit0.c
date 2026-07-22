#include "exit0.h"
#include "led.h"

void EXIT0_Init(void)
{
	//开启AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		
	//配置中断线
	// wk_up=pa0 key_0=pc5 key_1=pa15
	AFIO->EXTICR[0] &= ~(0xF<<0);
		
	AFIO->EXTICR[1] &= ~(0xF<<4);
	AFIO->EXTICR[1] |= (0x2<<4);
	
	AFIO->EXTICR[3] &= ~(0xF<<12);
		
	//配置中断方式
	//wk_up中断，wk_up为高电平有效，所以配置为上升沿中断
	EXTI->IMR &=~(0x1<<0);
	EXTI->IMR |=(0x1<<0);
	
	EXTI->RTSR &=~(0x1<<0);
	EXTI->RTSR |=(0x1<<0);
	
	//key_0中断,key_0为低电平有效，所以配置为下降沿中断
	EXTI->IMR &=~(0x1<<5);
	EXTI->IMR |=(0x1<<5);
		
	EXTI->FTSR &=~(0x1<<5);
	EXTI->FTSR |=(0x1<<5);
		
	//key_1中断，key_1低电平有效，所以配置为下降沿中断
	EXTI->IMR &=~(0x1<<15);
	EXTI->IMR |=(0x1<<15);
		
	EXTI->FTSR &=~(0x1<<15);
	EXTI->FTSR |=(0x1<<15);
		
	// 开启 IRQ6（EXTI0）
	NVIC->ISER[0] |= (1 << 6);

	// 开启 IRQ23（EXTI9_5）
	NVIC->ISER[0] |= (1 << 23);

	// 开启 IRQ40（EXTI15_10）
	NVIC->ISER[1] |= (1 << (40 - 32));   // 即 bit8
		
}

void EXTI0_IRQHandler(void)
{
    //if()
}

void EXTI9_5_IRQHandler(void)
{
    LED_RED_ON();
}

void EXTI15_10_IRQHandler(void)
{
    LED_GREEN_ON();
}
