#ifndef __SYSTICK_H
#define __SYSTICK_H 			   
#include "stm32f10x.h"


// cycles per microsecond
static volatile uint32_t usTicks = 0;
// 滴答定时器计数变量 ,49天后溢出
static volatile uint32_t sysTickUptime = 0;

void SysTick_IRQ(void);
uint32_t GetSysTime_us(void);
float getDeltaT(uint32_t);
float getDeltaT1(uint32_t,u8);

extern u8 schedulercnt_1ms;
extern u8 schedulercnt_2ms;
extern u8	schedulercnt_5ms;
extern u8	schedulercnt_10ms;
extern u8	schedulercnt_20ms;



#endif
