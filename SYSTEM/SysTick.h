#ifndef __SYSTICK_H
#define __SYSTICK_H 			   
#include "stm32f10x.h"

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
