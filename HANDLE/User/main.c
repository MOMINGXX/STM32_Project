#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "LED.h"
#include "USART.h"
#include "KEY.h"
#include "ROCKER.h"
#include "MPU6050.h"

extern __IO uint16_t Rocker_Value_BUFF[NUMCHANNEL];

uint8_t i;

int main()
{
	OLED_Init();
	LED_Init();
	KEY_Init();
	Usart_Init();
	ROCKER_Init();
	MPU6050_Init();
	OLED_ShowString(1,1," HANDLE TEST !");

	MPU6050_Data Data;

	while(1)
	{
		if(ADD == KEY_GetNumber())
		{
			OLED_Clear();
			OLED_ShowNum(2,1,Rocker_Value_BUFF[0],4);
			OLED_ShowNum(2,9,Rocker_Value_BUFF[1],4);
			OLED_ShowNum(3,1,Rocker_Value_BUFF[2],4);
			OLED_ShowNum(3,9,Rocker_Value_BUFF[3],4);
			OLED_ShowNum(4,1,Rocker_Value_BUFF[4],4);
		}
		
		else if(REDECE == KEY_GetNumber())
		{
			OLED_Clear();
			OLED_ShowNum(2,1,MPU6050_GetID(),2);	
		}
		else if(STOP == KEY_GetNumber())
		{
			OLED_Clear();
			OLED_ShowSignedNum(2,1,Data.ACCEL_XOUT,5);
			OLED_ShowSignedNum(2,9,Data.ACCEL_YOUT,5);
			OLED_ShowSignedNum(3,1,Data.ACCEL_ZOUT,5);
			OLED_ShowSignedNum(3,9,Data.GYRO_XOUT,5);
			OLED_ShowSignedNum(4,1,Data.GYRO_YOUT,5);
			OLED_ShowSignedNum(4,1,Data.GYRO_ZOUT,5);
		}
	}
}

