#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

#define RXHEX_MAX 4
#define RXCHA_MAX 100

//#define RX_HEX

extern uint8_t Usart_RxHEX[];
extern char Usart_RxCharacter[];
extern uint8_t Usart_RxFlag;

//´®¿Ú
#define SPECIFIE_USARTx                     USART1
#define SPECIFIE_USART_CLK                  RCC_APB2Periph_USART1
#define SPECIFIE_USART_APBxCLKCMD           RCC_APB2PeriphClockCmd
#define SPECIFIE_USART_BAUDRATE             115200

//´®¿ÚÒý½Å
#define SPECIFIE_USART_GPIO_CLK             RCC_APB2Periph_GPIOA
#define SPECIFIE_USART_GPIO_APBxCLKCMD      RCC_APB2PeriphClockCmd

#define SPECIFIE_USART_TX_GPIO_PIN          GPIO_Pin_9
#define SPECIFIE_USART_TX_GPIO_PORT         GPIOA
#define SPECIFIE_USART_RX_GPIO_PIN          GPIO_Pin_10
#define SPECIFIE_USART_RX_GPIO_PORT         GPIOA

#define SPECIFIE_USART_IRQChannel           USART1_IRQn
#define SPECIFIE_USART_IRQHNADLER           USART1_IRQHandler

void Usart_Init();
uint8_t Usart_GetRxFlag();
void Usart_sprintf(char *format, ...);
void Usart_SendByte(USART_TypeDef *USARTx,uint8_t Byte);
void Usart_SendHalfWorld(USART_TypeDef *USARTx,uint16_t Byte);
void Usart_SendString(USART_TypeDef *USARTx,char *String);
void Usart_SendBuff(USART_TypeDef *USARTx ,uint8_t *Buff, uint16_t Length);
void Usart_SendNumber(USART_TypeDef *USARTx,uint32_t Number,uint8_t Length);

#endif /*__USART_H__*/


