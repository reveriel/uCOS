#include "delay.h"
#include "sys.h"
#include "SysTick.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 




//void SysTick_Handler(void) 
//{	
//	sysTickUptime++;
//	schedulercnt_1ms++;
//	schedulercnt_2ms++;
//	schedulercnt_5ms++;
//	schedulercnt_10ms++;
//	schedulercnt_20ms++;			   
//	OSIntEnter();		//进入中断
//    OSTimeTick();       //调用ucos的时钟服务程序               
//    OSIntExit();        //触发任务切换软中断

//}



void delay_init()	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	SysTick_Config(SystemCoreClock / 1000); // ms
}								    



