#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "Delay.h"

typedef enum 
{
    DHT11_INPUT,
    DHT11_OUTPUT
}DHT11_InitTypedef;

#define DHT11_GPIO_CLK              RCC_APB2Periph_GPIOB
#define DHT11_GPIO_APBxCLKCMD       RCC_APB2PeriphClockCmd

#define DHT11_GPIO_PIN              GPIO_Pin_2
#define DHT11_GPIO_PORT             GPIOB

#define DHT11_WIREBUS(BitValue)     GPIO_WriteBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN,(BitAction)BitValue);
#define DHT11_CLK_ENABLE			DHT11_GPIO_APBxCLKCMD(DHT11_GPIO_CLK,ENABLE);

uint8_t DHT11_Read_Byte();
void DHT11_Read_Data(uint8_t *TempH,uint8_t *TempL,uint8_t *HumiH,uint8_t *HumiL);

#endif /*__DHT11_H__*/


