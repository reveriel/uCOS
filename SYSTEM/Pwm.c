#include "Pwm.h"

/*
PWM1   PA2  tim2_CH3
PWM2   PA3  tim2_CH4
PWM3   PA8  tim1_CH1
PWM4   PA11 tim1_CH4



高电平有效
*/
#define PWM1(X) TIM2->CCR3 = X
#define PWM2(X)	TIM2->CCR4 = X
#define PWM3(X)	TIM1->CCR1 = X
#define PWM4(X) TIM1->CCR4 = X
	
void PWM_OutInit(void){
	
	uint16_t PrescalerValue = 0;

	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	GPIO_InitTypeDef 			GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启TIM1、2,GPIO,// no AFIO外设时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_11;
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
	
	/* PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM1, ENABLE);	
	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能TIM1的主输出，因为TIM1是高级定时器  所以要这么做
	
	
	PWM1(0);
	PWM2(0);
	PWM3(0);
	PWM4(0);
}
void PWMControl(float PWM[]){
	
	TIM2->CCR3 =PWM[0]*1.08>=1000?999:PWM[0]*1.08;
	TIM2->CCR4 =PWM[1]*1.01>=1000?999:PWM[1]*1.01;
	TIM1->CCR1 =PWM[2]>=1000?999:PWM[2];
	TIM1->CCR4 =PWM[3]>=1000?999:PWM[3];
}
