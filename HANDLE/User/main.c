#include "MODEDATA.h"

int main()
{
	OLED_Init();
	LED_Init();
	KEY_Init();
	Usart_Init();
	ROCKER_Init();
	MPU6050_Init();
	NRF24L01_Init();
	
	NRF24L01_Check_detection();
	while(1)
	{
 		KEY_SCAN();
		Mode_Option();
	}
}
