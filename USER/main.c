#include "include.h"
//#include "delay.h"
#include "includes.h"
#define LED_ON() 	GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define LED_OFF() 	GPIO_ResetBits(GPIOA, GPIO_Pin_15)
/*
#define		GPIO_SetBits(GPIOA, GPIO_Pin_2);
#define		GPIO_SetBits(GPIOA, GPIO_Pin_3);
#define		GPIO_SetBits(GPIOA, GPIO_Pin_8);
#define		GPIO_SetBits(GPIOA, GPIO_Pin_11);
#define		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
#define		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
#define		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
#define		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
*/
short GX, GY, GZ,T,AX,AY,AZ;
float GX_F,GY_F,GZ_F,T_F,AX_F,AY_F,AZ_F;
unsigned char BUF[20];       			//recive data buffer
char  test=0; 				 			//IIC



/*

#define START_TASK_PRIO      			10 
#define START_STK_SIZE  				64
OS_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *pdata);	

#define LED1_TASK_PRIO       			7 
#define LED1_STK_SIZE  		    		64
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
void led1_task(void *pdata);



#define LED2_TASK_PRIO       			6 
#define LED2_STK_SIZE  					64
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
void led2_task(void *pdata);



void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);						   
 	OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);	 				   
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}


int i;
int j;

int i,j;
void led1_task(void *pdata)
{	 	
	while(1)
	{
		printf("i = %d\n", i++);
		delay_ms(20);
	};
}

void led2_task(void *pdata)
{	  
	while(1)
	{
		printf("j = %d\n",j++);
		delay_ms(30);
	};
}


int main(void)
{
	//GPIO_Configuration();
	Usart_Configuration();
	delay_init();	     //延时初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO);
	OSStart();
		
}
*/

void delay_m(int ms)
{
	 ms = ms * 1000;
	while (ms--);
}

int main(void)
{
	GPIO_Configuration();
	while (1) {
		
		LED_ON();
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
//		GPIO_SetBits(GPIOA, GPIO_Pin_3);
//		GPIO_SetBits(GPIOA, GPIO_Pin_8);
//		GPIO_SetBits(GPIOA, GPIO_Pin_11);
		delay_m(10000);
		LED_OFF();
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		delay_m(10000);
		
	}
}
