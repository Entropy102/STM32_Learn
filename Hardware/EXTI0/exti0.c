#include "exti0.h"
#include "led.h"

void EXTI0_Init(void)
{
	// 开启AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	// 配置中断线
	// wk_up=pa0 key_0=pc5 key_1=pa15
	AFIO->EXTICR[0] &= ~(0xF<<0);
	AFIO->EXTICR[1] &= ~(0xF<<4);
	AFIO->EXTICR[1] |= (0x2<<4);
	AFIO->EXTICR[3] &= ~(0xF<<12);

	// 配置中断方式
	// wk_up中断，wk_up为高电平有效，所以配置为上升沿中断
	EXTI->IMR &=~(0x1<<0);
	EXTI->IMR |=(0x1<<0);
	EXTI->RTSR &=~(0x1<<0);
	EXTI->RTSR |=(0x1<<0);

	// key_0中断,key_0为低电平有效，所以配置为下降沿中断
	EXTI->IMR &=~(0x1<<5);
	EXTI->IMR |=(0x1<<5);
	EXTI->FTSR &=~(0x1<<5);
	EXTI->FTSR |=(0x1<<5);

	// key_1中断，key_1低电平有效，所以配置为下降沿中断
	EXTI->IMR &=~(0x1<<15);
	EXTI->IMR |=(0x1<<15);
	EXTI->FTSR &=~(0x1<<15);
	EXTI->FTSR |=(0x1<<15);

	// 开启 IRQ6（EXTI0）
	NVIC->ISER[0] |= (1 << 6);
	// 开启 IRQ23（EXTI9_5）
	NVIC->ISER[0] |= (1 << 23);
	// 开启 IRQ40（EXTI15_10）
	NVIC->ISER[1] |= (1 << (40 - 32));   // 即bit8
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0)) {
        EXTI->PR = (1 << 0);
        LED_RED_OFF();
        LED_GREEN_OFF();
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1 << 5)) {
        EXTI->PR = (1 << 5);
        // toggle RED (PA8, active low)
        if (GPIOA->ODR & (1 << 8))
            LED_RED_ON();
        else
            LED_RED_OFF();
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1 << 15)) {
        EXTI->PR = (1 << 15);
        // toggle GREEN (PD2, active low)
        if (GPIOD->ODR & (1 << 2))
            LED_GREEN_ON();
        else
            LED_GREEN_OFF();
    }
}
