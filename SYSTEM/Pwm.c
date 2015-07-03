#include "Pwm.h"








void PWM_Configuration(void){
	
	uint16_t PrescalerValue = 0;

	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	GPIO_InitTypeDef 			GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);//开启TIM1、2,GPIO,// no AFIO外设时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Compute the prescaler value */
	PrescalerValue	= (uint16_t) (SystemCoreClock / (17000 *1000)) - 1;//17khz的pwm
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;		//
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//pwm时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	

	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM1, ENABLE);	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能TIM1的主输出，因为TIM1是高级定时器  所以要这么做
	
}



//void PWM_Configuration(void){
//	
//	uint16_t PrescalerValue = 0;

//	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  			TIM_OCInitStructure;
//	GPIO_InitTypeDef 			GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启TIM1、2,GPIO,// no AFIO外设时钟

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);


//	/* Compute the prescaler value */
//	PrescalerValue	= (uint16_t) (SystemCoreClock / (17000 *1000)) - 1;//17khz的pwm
//	/* Time base configuration */
//	TIM_TimeBaseStructure.TIM_Period = 999;		//
//	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//pwm时钟分频
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//	
//	/* PWM1 Mode configuration: Channel */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
//	TIM_ARRPreloadConfig(TIM1, ENABLE);
//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	TIM_Cmd(TIM1, ENABLE);	
//	TIM_Cmd(TIM2, ENABLE);
//	TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能TIM1的主输出，因为TIM1是高级定时器  所以要这么做

//}

void PWMControl(float PWM[]){
	
//	TIM2->CCR1 =PWM[0]*1.08>=1000?999:PWM[0]*1.08;
//	TIM1->CCR1 =PWM[1]*1.01>=1000?999:PWM[1]*1.01;
//	TIM3->CCR2 =PWM[2]>=1000?999:PWM[2];
//	TIM3->CCR1 =PWM[3]>=1000?999:PWM[3];
	
	PWM1 =PWM[0]*1.08>=1000?999:PWM[0]*1.08;
	PWM2 =PWM[1]*1.01>=1000?999:PWM[1]*1.01;
	PWM3 =PWM[2]>=1000?999:PWM[2];
	PWM4 =PWM[3]>=1000?999:PWM[3];
}

