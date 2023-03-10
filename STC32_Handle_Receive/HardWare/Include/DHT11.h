#ifndef __DHT11_H__
#define __DHT11_H__

#include <STC32G.h>
#include "Delay.h"

typedef struct
{
	int8_t TempH;
	int8_t TempL;
	int8_t HumiH;
	int8_t HumiL;
}DHT11_Data;

sbit DHT11_DATA = P3^4;

void DHT11_GPIO_Config();
void DHT11_Read_Data(DHT11_Data * DATA);

#endif   /* __DHT11_H__*/