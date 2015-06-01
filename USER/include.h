#ifndef __INCLUDE_H_
#define __INCLUDE_H_
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
//#include "inter.h"
//#include "math.h"
//#include "pwm.h"
//#include "scope.h"
//#include "exchange.h"
//#include "send.h"
//#include "ReadAngle.h"
//#include "FlyControl.h"
//#include "Spi.h"
//#include "Nrf24l01.h"
//#include "SysTick.h"

#define MOTOL1 GPIO_Pin_2
#define MOTOL2 GPIO_Pin_3
#define MOTOL3 GPIO_Pin_8
#define MOTOL4 GPIO_Pin_11
#define TEST 4

extern u32 MainTime;
extern u32 Second;
extern u8 LoopFlag;
extern float PWM[4];

void GPIO_Configuration(void);


#endif
