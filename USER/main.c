#include "include.h"


short GX,GY,GZ,T,AX,AY,AZ;
float GX_F,GY_F,GZ_F,T_F,AX_F,AY_F,AZ_F;
unsigned char BUF[20];       			//接收数据缓存区
char  test=0; 				 			//IIC


int main(void)
{
	GPIO_Configuration();
	Usart_Configuration();
	while (1) {
		printf("hello \n");
	}
}
