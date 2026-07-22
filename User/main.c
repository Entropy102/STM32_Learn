#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "exit0.h"
#include "delay.h"


int main(void)
{
    LED_Init();
	KEY_Init();
    delay_init();
	EXIT0_Init();
	
	LED_GREEN_OFF();
	LED_RED_OFF();
	
	//uint32_t count=0;

    while(1)
    {
		
			/*if(Key_Wk_Up())
			{
				LED_GREEN_ON();
				LED_RED_ON();
			}else if(Key_Key_0())
			{
				LED_RED_ON();
			}else if(Key_Key_1())
			{
				LED_GREEN_ON();
			}else 
			{
				LED_GREEN_OFF();
				LED_RED_OFF();
			}
			if(Key_Key_0())
			{
				count ++;

				delay_ms(200);
			}*/
		
		
			
    }
}
