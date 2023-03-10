#ifndef __SPI_H__
#define __SPI_H__

#include <STC32G.H>

sbit SPI_CS = P5^0;
sbit SPI_SCK = P1^5;
sbit SPI_MISO = P1^4;
sbit SPI_MOSI = P1^3;

#define SOFT    0
#define HARD    1

void SPI_Init();
void SPI_SendByte(uint8_t Byte);
uint8_t SPI_ReceiveByte();
uint8_t SPI_Send_ReceiveByte(uint8_t Byte);

#endif /*__SPI_H__*/