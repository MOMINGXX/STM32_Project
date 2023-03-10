#include "MODEDATA.h"

int main()
{
	//各模块初始化
	OLED_Init();
	LED_Init();
	KEY_Init();
	Usart_Init();
	ROCKER_Init();
	MPU6050_Init();
	NRF24L01_Init();
	
	NRF24L01_Check_detection();		//检测NRF24L01是否连接正常
	while(1)
	{
 		KEY_SCAN();
		Mode_Option();
	}
}
