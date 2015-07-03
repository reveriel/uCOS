#ifndef __MOTOR_H
#define __MOTOR_H
#include "include.h"

#define PWM1  	TIM2->CCR1
#define PWM2	TIM1->CCR1
#define PWM3	TIM3->CCR2
#define PWM4	TIM3->CCR1



void PWM_Configuration(void);
void PWMControl(float*);

#endif
