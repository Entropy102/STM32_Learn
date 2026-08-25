#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "exti0.h"
#include "delay.h"


int main(void)
{
    LED_Init();
	KEY_Init();
    delay_init();
	EXTI0_Init();
	
	LED_GREEN_OFF();
	LED_RED_OFF();
	
	//uint32_t count=0;

    while(1)
    {

    }
}
