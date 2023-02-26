#ifndef __SOFT_SPI_H__
#define __SOFT_SPI_H__

#include "stm32f10x.h"                  // Device header
	
#define SPI_GPIO_CLK            RCC_APB2Periph_GPIOA
#define SPI_GPIO_APBxCLKCMD     RCC_APB2PeriphClockCmd

#define SPI_GPIO_PORT          	GPIOA
		
#define SPI_CS_GPIO_PIN         GPIO_Pin_4
		
#define SPI_SCK_GPIO_PIN        GPIO_Pin_5
	
#define SPI_MISO_GPIO_PIN       GPIO_Pin_6
		
#define SPI_MOSI_GPIO_PIN       GPIO_Pin_7

void SOFT_SPI_Config();
void SPI_W_CS(uint8_t BitValue);
uint8_t SOFT_SPI_SwapByte(uint8_t ByteSend);

#endif	/*__SOFT_SPI_H__*/


