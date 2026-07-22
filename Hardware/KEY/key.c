#include "key.h"

//按钮初始化
void KEY_Init(void)
{
	//开启GPIOA C 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
	
	//开启AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	/* 关闭 JTAG，保留 SWD */
	AFIO->MAPR &= ~(0x7 << 24);
	AFIO->MAPR |= (0x2 << 24);
	
	//Wk_Up_Init(PA0)
	GPIOA->CRL &=~(0xF<<0);
	GPIOA->CRL |=(0x8<<0);//输入下拉，默认输入0，因为Wk_Up是高电平有效
	GPIOA->ODR &= ~(1 << 0);//ODR0置0，表示PA0接内部下拉电阻
	
	//Key_0_Init(PC5)
	GPIOC->CRL &=~(0xF<<20);
	GPIOC->CRL |=(0x8<<20);//输入上拉，默认输入1，因为Key_0是低电平有效
	GPIOC->ODR |=(1<<5);//ODR5置1，表示PC5接内部上拉电阻
	
	//Key_1_Init(PA15)
	GPIOA->CRH &=~((uint32_t)0xF<<28);
	GPIOA->CRH |=(0x4<<28);//外部上拉，浮空输入
	
}

// 点击WK_UP按钮，DS0,DS1全灭
uint8_t Key_Wk_Up(void)
{	
	if(GPIOA->IDR & (1<<0))
	{
		return 1;
	}
	return 0;
}

//点击KEY_0,DS0亮
uint8_t Key_Key_0(void)
{
	if((GPIOC->IDR & (1<<5)) == 0)
	{
		return 1;
	}
	return 0;
}

//点击KEY_1,DS1亮
uint8_t Key_Key_1(void)
{	
	if((GPIOA->IDR & (1 << 15)) == 0)
    {
        return 1;
    }
    return 0;
}

