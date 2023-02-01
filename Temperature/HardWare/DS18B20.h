#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define DS18B20_CONVERT_T 		0x44
#define DS18B20_SKIP_ROM 		0xCC
#define DS18B20_READ_SCRATCHPAD	0xBE

typedef enum 
{
    DS18B20_INPUT,
    DS18B20_OUTPUT
}DS18B20_InitTypedef;

#define DS18B20_GPIO_CLK                RCC_APB2Periph_GPIOA
#define DS18B20_GPIO_APBxCLKCMD         RCC_APB2PeriphClockCmd

#define DS18B20_GPIO_PIN                GPIO_Pin_1
#define DS18B20_GPIO_PORT               GPIOA

#define DS18B20_WIREBUS(BitValue)       GPIO_WriteBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN,(BitAction)BitValue);
#define DS18B20_CLK_ENABLE				DS18B20_GPIO_APBxCLKCMD(DS18B20_GPIO_CLK,ENABLE);

void DS18B20_Init();
uint8_t DS18B20_ReadBit();
float DS18B20_ReadT();
void DS18B20_ConvertT();
uint8_t DS18B20_ReadByte();
uint8_t DS18B20_ReadBit();
void DS18B20_WriteBit(uint8_t Bit);
void DS18B20_WriteByte(uint8_t Byte);

#endif  /*__DS15B20_H__*/


