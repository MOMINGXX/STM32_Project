#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "LED.h"
#include "USART.h"
#include "KEY.h"
#include "ROCKER.h"
#include "MPU6050.h"

extern __IO uint16_t Rocker_Value_BUFF[NUMCHANNEL];
MPU6050_Data Data;
uint8_t KEY_NUM,ID,Mode = 2;

void Deal_Mode_Select();

int main()
{
	OLED_Init();
	LED_Init();
	KEY_Init();
	Usart_Init();
	ROCKER_Init();
	MPU6050_Init();

	while(1)
	{
		KEY_NUM = KEY_GetNumber();
		Deal_Mode_Select();
		Delay_ms(500);
	}
}

void Deal_Mode_Select()
{
	if(ADD == KEY_NUM)
	{
		OLED_Clear();
		Mode = 0;
	}
	else if(REDECE == KEY_NUM)
	{
		OLED_Clear();
		Mode = 1;
	}
	else if(STOP == KEY_NUM)
	{
		OLED_Clear();
		Mode = 2;
	}
	switch(Mode)
	{
		case 0:	
			OLED_ShowString(1,1," Rocker Value !");
			OLED_ShowNum(2,1,Rocker_Value_BUFF[0],4);
			OLED_ShowNum(2,9,Rocker_Value_BUFF[1],4);
			OLED_ShowNum(3,1,Rocker_Value_BUFF[2],4);
			OLED_ShowNum(3,9,Rocker_Value_BUFF[3],4);
			OLED_ShowNum(4,1,Rocker_Value_BUFF[4],4);
			break;
		case 1:	
			OLED_ShowString(1,1," MPU6050 Value !");
			MPU6050_GetData(&Data);
			OLED_ShowSignedNum(2,1,Data.ACCEL_XOUT,5);
			OLED_ShowSignedNum(2,9,Data.ACCEL_YOUT,5);
			OLED_ShowSignedNum(3,1,Data.ACCEL_ZOUT,5);
			OLED_ShowSignedNum(3,9,Data.GYRO_XOUT,5);
			OLED_ShowSignedNum(4,1,Data.GYRO_YOUT,5);
			OLED_ShowSignedNum(4,9,Data.GYRO_ZOUT,5);
			break;
		case 2:	
			OLED_ShowString(1,3," MPU6050 ID !");
			ID = MPU6050_GetID();
			OLED_ShowHexNum(2,1,ID,2);	
			break;
		default:
			OLED_ShowString(1,1,"Select ERROR !");
			break;
	}
}