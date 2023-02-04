#ifndef	__Deal_H__
#define __Deal_H__

//#include "USART.h"
#include "EEPROM.h"
#include "OLED.h"
#include "DS18B20.h"
#include "DHT11.h"
#include "TIMCOUNT.h"

void Deal_Init();
void Key_Get();
void Deal_Mode_Select();
void Temp_Alarm();
void OLED_DS18B20_Temp(uint8_t x);
void OLED_DHT11_Temp();

#endif	/*__Deal_H__*/

