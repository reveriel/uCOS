#ifndef _MPU6050_H_
#define _MPU6050_H_
#include "stm32f10x.h"

#define SCL_H         GPIOB->BSRR = GPIO_Pin_10
#define SCL_L         GPIOB->BRR  = GPIO_Pin_10 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_11
#define SDA_L         GPIOB->BRR  = GPIO_Pin_11

#define SCL_read      GPIOB->IDR  & GPIO_Pin_10
#define SDA_read      GPIOB->IDR  & GPIO_Pin_11

#define I2C_Speed 						400000
#define I2C1_MPU6050					0xd0


/***********宏定义MPU6050内部寄存器地址****************/
#define	SMPLRT_DIV					0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIGM							0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG					0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG				0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H				0x3B
#define	ACCEL_XOUT_L				0x3C
#define	ACCEL_YOUT_H				0x3D
#define	ACCEL_YOUT_L				0x3E
#define	ACCEL_ZOUT_H				0x3F
#define	ACCEL_ZOUT_L				0x40
#define	TEMP_OUT_H					0x41
#define	TEMP_OUT_L					0x42
#define	GYRO_XOUT_H					0x43
#define	GYRO_XOUT_L					0x44	
#define	GYRO_YOUT_H					0x45
#define	GYRO_YOUT_L					0x46
#define	GYRO_ZOUT_H					0x47
#define	GYRO_ZOUT_L					0x48
#define	PWR_MGMT_1					0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I						0x75	//IIC地址寄存器(默认数值0x68，只读)  之前是75
#define	MPU6050_Addr   0xD0	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址起脚不同修改


//全局变量声明
#define Gyro_Gr	0.0010653				//角速度变成弧度	此参数对应陀螺2000度每秒

extern unsigned char BUF[20];       	//接收数据缓存区
extern char  test; 					 	//IIC

extern short GX,GY,GZ,T,AX,AY,AZ;
extern float GX_F,GY_F,GZ_F,T_F,AX_F,AY_F,AZ_F;



void I2C_Congiguration(void);
int Init_MPU6050(void);

unsigned char Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		     //void;
unsigned char I2C_RadeByte(void);
void I2C_SendByte(u8 SendByte);
unsigned char I2C_WaitAck(void) ;
void I2C_NoAck(void);
void I2C_Ack(void);
void I2C_Stop(void);
void READ_MPU6050(void);
void I2C_GPIO_Config(void);
unsigned char I2C_Start(void);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
#endif

