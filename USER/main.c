#include "include.h"
//#include "includes.h"

#define PWM1(X) TIM2->CCR3 = X
#define PWM2(X)	TIM2->CCR4 = X
#define PWM3(X)	TIM1->CCR1 = X
#define PWM4(X) TIM1->CCR4 = X

#define LED_ON() 	GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define LED_OFF() 	GPIO_ResetBits(GPIOA, GPIO_Pin_15)


float GX_F, GY_F, GZ_F, T_F, AX_F, AY_F, AZ_F;			// global var ,for mpu6050_read()
float Roll, Yaw, Pitch;


int main(void)
{
	u16 time = 0;
	Usart_Configuration();
	MPU6050_Configuration();
	PWM_Configuration();
	
	SysTick_Config(SystemCoreClock / 1000); // ms
	
	while (1) {
		

			READ_MPU6050();
			IMUupdate(GX_F,GY_F,GZ_F,AX_F,AY_F,AZ_F);
//			printf("%f   \n", AZ_F);
			printf("%30f    %30f    %30f    ", Roll, Yaw, Pitch);
			
		
	}
	
}
     