#include "iic.h"
#include "delay.h"
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//IIC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//初始化IIC
void IIC_Init(void) 
{			
	GPIO_InitTypeDef  GPIO_InitStructure;

	// PB10, out ,, PB11, out
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	SCL_H;
	SDA_H;
}
//产生IIC起始信号
void IIC_delay()
{
	delay_us(5);
}

u8 IIC_Start(void)
{
	SDA_H;
	SCL_H;
	IIC_delay();
	if(!SDA_read)
		return 0;//SDA线为低电平,则总线忙,退出
 	SDA_L;		//START:when CLK is high,DATA change form high to low 
	IIC_delay();
	if(SDA_read)
		return 0;	//SDA线为高电平,则总线出错,退出
	SCL_L;		//钳住I2C总线，准备发送或接收数据 
	return 1;
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	IIC_delay();
	SCL_H; 
	SDA_H;//发送I2C总线结束信号
	IIC_delay();						   	
}
//等待应答信号到来
//返回值：1，ack
//        0，noack
u8 IIC_Wait_Ack(void)
{
	SCL_L;
	IIC_delay();
	SDA_H;
	IIC_delay();   
	SCL_H;
	IIC_delay();
	if (SDA_read)
	{
		SCL_L;
		IIC_delay();
		return 1;
	}
	SCL_L;//时钟输出0 	
	IIC_delay();
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	SCL_L;
	SDA_L;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	SCL_L;
	SDA_H;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        if(txd&0x80)
			SDA_H;
		else
			SDA_L;
        txd<<=1; 
		IIC_delay();   //对TEA5767这三个延时都是必须的
		SCL_H;
		IIC_delay();
		SCL_L;
		IIC_delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
    for(i=0;i<8;i++ )
	{
        SCL_L;
        IIC_delay();
		SCL_H;
        receive<<=1;
        if(SDA_read)
			receive++;   
		IIC_delay();
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}





