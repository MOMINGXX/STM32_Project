#ifndef __HC595_H__
#define __HC595_H__

#include <STC32G.h>	

sbit HC595_PCLK = P4^5;
sbit HC595_SRCLR = P4^6;
sbit HC595_SER = P4^7;

void HC595_Init();
void HC595_SendData(uint8_t Data);

#endif	/*__HC595_H__*/