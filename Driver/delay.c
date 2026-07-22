#include "delay.h"

static uint32_t us_tick;

void delay_init(void)
{
    us_tick = SystemCoreClock / 1000000;
}

void delay_us(uint32_t us)
{
    uint32_t ticks = us * us_tick;
    while (ticks--) {
        __NOP();
    }
}

void delay_ms(uint32_t ms)
{
    while (ms--) {
        delay_us(1000);
    }
}
