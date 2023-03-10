#ifndef __DELAY_H__
#define __DELAY_H__

#include "STC32G.h"

#define SYS_CLK 24000000L
#ifndef SYS_CLK 
#define SYS_CLK 11059200L
#endif

void Delay_us(uint16_t xus);
void Delay_ms(uint16_t xms);
void Delay_s(uint16_t xs);

//—”≥Ÿ1Œ¢√Î
void Delay1us();
//—”≥Ÿ5Œ¢√Î
void Delay5us();
//—”≥Ÿ10Œ¢√Î
void Delay10us();
//—”≥Ÿ15Œ¢√Î
void Delay15us();
//—”≥Ÿ20Œ¢√Î
void Delay20us();
//—”≥Ÿ50Œ¢√Î
void Delay50us();	
//—”≥Ÿ100Œ¢√Î
void Delay100us();	
//—”≥Ÿ1∫¡√Î
void Delay1ms();			

#endif   /* __DELAY_H__*/