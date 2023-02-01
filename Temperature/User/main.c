#include "stm32f10x.h"                  // Device header
#include "Deal.h"
int main()
{
	Deal_Init();
	while(1)
	{
		OLED_DS18B20_Temp();
		OLED_DHT11_Temp();
		Delay_s(1);
	}
} 

