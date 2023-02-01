#ifndef	__I2C_H__
#define __I2C_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//IIC GPIO
#define IIC_SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define IIC_SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define IIC_GPIO_APBxCLKCMD      RCC_APB2PeriphClockCmd

#define IIC_SCL_GPIO_PIN          GPIO_Pin_6
#define IIC_SCL_GPIO_PORT         GPIOB
#define IIC_SDA_GPIO_PIN          GPIO_Pin_7
#define IIC_SDA_GPIO_PORT         GPIOB

//#define IIC_SCL(Bit)              GPIO_WriteBit(IIC_SCL_GPIO_PORT,IIC_SCL_GPIO_PIN,(BitAction)Bit);
//#define IIC_SDA(Bit)              GPIO_WriteBit(IIC_SDA_GPIO_PORT,IIC_SDA_GPIO_PIN,(BitAction)Bit);  

void IIC_Ack();
void IIC_Init();
void IIC_Start();
void IIC_Stop();
void IIC_SendByte(uint8_t Byte);
uint8_t IIC_ReceiveByte();
uint8_t IIC_ReceiveAck();
void IIC_SendAck(uint8_t Ack);

#endif	/*__I2C_H__*/

