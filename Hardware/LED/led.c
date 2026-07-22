#include "led.h"
void LED_Init(void)
{
    //开启 GPIOA D时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	
    // PA8 配置输出
    GPIOA->CRH &= ~(0xF<<0);
    // 50MHz 推挽输出
    GPIOA->CRH |= (0x3<<0);
	
	// PD2配置输出
	GPIOD->CRL &= ~(0xF<<8);
	// 50MHz 推挽输出
	GPIOD->CRL |=(0x3<<8);


    // 初始关闭LED
    GPIOA->BSRR = (1<<8);
	GPIOD->BSRR = (1<<2);
}

//红灯(DS0)PA8,低电平亮
void LED_RED_ON(void)
{
    GPIOA->BSRR = (1<<(8+16));
}

void LED_RED_OFF(void)
{
    GPIOA->BSRR = (1<<8);
}

//绿灯(DS1)PD2,低电平亮
void LED_GREEN_ON(void)
{
    GPIOD->BSRR = (1<<(2+16));
}

void LED_GREEN_OFF(void)
{
    GPIOD->BSRR = (1<<2);
}
