#ifndef __USER_I2C_H__
#define __USER_I2C_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//IIC GPIO
#define IIC_GPIO_CLK                RCC_APB2Periph_GPIOA
#define IIC_GPIO_APBxCLKCMD         RCC_APB2PeriphClockCmd

#define IIC_GPIO_PORT               GPIOA
#define IIC_SCL_GPIO_PIN            GPIO_Pin_11
#define IIC_SDA_GPIO_PIN            GPIO_Pin_12

void IIC_Init();
void IIC_Start();
void IIC_Stop();
void IIC_SendByte(uint8_t Byte);
uint8_t IIC_ReceiveByte();
uint8_t IIC_ReceiveAck();
void IIC_SendAck(uint8_t Ack);

#endif
