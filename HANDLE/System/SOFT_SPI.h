#ifndef __SOFT_SPI_H__
#define __SOFT_SPI_H__

#include "stm32f10x.h"                  // Device header
	
#define SPI_GPIO_CLK            RCC_APB2Periph_GPIOB
#define SPI_GPIO_APBxCLKCMD     RCC_APB2PeriphClockCmd

#define SPI_GPIO_PORT          	GPIOB	
#define SPI_CS_GPIO_PIN         GPIO_Pin_7
#define SPI_SCK_GPIO_PIN        GPIO_Pin_13
#define SPI_MISO_GPIO_PIN       GPIO_Pin_14
#define SPI_MOSI_GPIO_PIN       GPIO_Pin_15

void SOFT_SPI_Config();
void SPI_W_CS(uint8_t BitValue);
uint8_t NRF24L01_Send_RecieveByte(uint8_t ByteSend);

#endif	/*__SOFT_SPI_H__*/


