#include "include.h"
#include "includes.h"

#define PWM1(X) TIM2->CCR3 = X
#define PWM2(X)	TIM2->CCR4 = X
#define PWM3(X)	TIM1->CCR1 = X
#define PWM4(X) TIM1->CCR4 = X



float GX_F, GY_F, GZ_F, T_F, AX_F, AY_F, AZ_F;			// global var ,for mpu6050_read()
float Roll, Yaw, Pitch;
float PWM[4];

u8 CtrData;

int main(void)
{

	int  cnt = 500000;
	Usart_Configuration();
	MPU6050_Configuration();
	PWM_Configuration();
	
	
	SysTick_Config(SystemCoreClock / 1000); // ms
	
	CtrData = 1;  
	
	
	PWM[0] = PWM[1] = PWM[2] = PWM[3] = 700;
	while (1) {
		
		if(schedulercnt_2ms >= 2)
		{	 
			cnt--;
			if (cnt <= 0) {
				PWM[0] = PWM[1] = PWM[2] = PWM[3] = 700;
				PWMControl(PWM);
			}
			
			READ_MPU6050();
			Control();
			PWMControl(PWM);
			
			schedulercnt_2ms = 0;

		}
		
	}
	
}


