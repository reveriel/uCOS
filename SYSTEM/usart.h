#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
  void Uart1_Init(u32 br_num);
	void Uart1_Put_String(unsigned char *Str);
	void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num);
	void Usart_Configuration(void);
	extern u8 TxBuffer[256];
	extern u8 RxBuffer[50];
	extern u8 CtrData;
#endif
