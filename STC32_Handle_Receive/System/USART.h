#ifndef __USART_H__
#define __USART_H__

#include "STC32G.h"
#include <stdio.h>
#include <stdarg.h>

#define sys_clk         24000000UL
#define BAUD            9600
#define BRT             (65536 - (sys_clk / BAUD / 4))

typedef enum
{
	USART1,
	USART3,	
}USART_TypeDef;

#define USART1	1
#define USART3	3
#define LENTH	19

extern uint8_t RX1_DAT[10];
extern bit Flag1;

extern uint8_t RX2_BUFF[LENTH];
extern uint8_t Flag3;

#define	PRINTF_SELECT 		 USART1		//选择 printf 函数所使用的串口，参数 UART1~UART2
 
void Usartx_Init();	
void Usartx_SendByte(USART_TypeDef USARTx,uint8_t Byte);
void Usartx_sprintf(USART_TypeDef USARTx,char *format, ...);
void Usartx_SendString(USART_TypeDef USARTx,uint8_t *String);
void Usartx_SendBuff(USART_TypeDef USARTx,uint8_t *Buff,uint16_t Len);
void Usartx_SendNumber(USART_TypeDef USARTx,uint32_t Number,uint8_t Length);

#endif   /* __USART_H__*/