#include "SysTick.h"



u8 schedulercnt_1ms=0;
u8 schedulercnt_2ms=0;
u8 schedulercnt_5ms=0;
u8 schedulercnt_10ms=0;
u8 schedulercnt_20ms=0;

static void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

// move to delay.c

void SysTick_IRQ(void)
{
	sysTickUptime++;
	schedulercnt_1ms++;
	schedulercnt_2ms++;
	schedulercnt_5ms++;
	schedulercnt_10ms++;
	schedulercnt_20ms++;
}

uint32_t GetSysTime_us(void) 
{
    register uint32_t ms, cycle_cnt;
    do {
        ms = sysTickUptime;
        cycle_cnt = SysTick->VAL;  //sysTick Current Value Register
    } while (ms != sysTickUptime);
    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void ANO_Hexacopter_board_Init(void)
{
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//初始化系统滴答定时器
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	
}


float getDeltaT(uint32_t currentT)
{
	static uint32_t previousT;
	float	deltaT = (currentT - previousT) * 1e-6;	
	previousT = currentT;
	
	return deltaT;
}
float getDeltaT1(uint32_t currentT,u8 i)
{
	static uint32_t previousT1[4] = {0,0,0,0};
	float	deltaT = (currentT - previousT1[i]) * 1e-6;	
	previousT1[i] = currentT;
	
	return deltaT;
}

