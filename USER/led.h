#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void led_Configuration(void);

// two controlable LED
// PB1,   LED,  blue
// PB12,  LED,  green




#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态

#define LED1_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_1)
#define LED1_OFF		digitalHi(GPIOB,GPIO_Pin_1)
#define LED1_ON			digitalLo(GPIOB,GPIO_Pin_1)

#define LED2_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_12)
#define LED2_OFF		digitalHi(GPIOB,GPIO_Pin_12)
#define LED2_ON			digitalLo(GPIOB,GPIO_Pin_12)

#endif