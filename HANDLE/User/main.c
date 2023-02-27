#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "LED.h"
#include "USART.h"
#include "KEY.h"
#include "ROCKER.h"
#include "MPU6050.h"
#include "NRF24L01.h"

extern __IO uint16_t Rocker_Value_BUFF[NUMCHANNEL];
MPU6050_Data Data;
ROCKER_Value Value;
uint8_t KEY_NUM,ID,Mode = 0;

uint8_t NRF24L01_RX_BUF[10];		//接收数据缓存
uint8_t NRF24L01_TX_BUF[10] = {"abcdefgh"};		//发射数据缓存

void Deal_Mode_Select();


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

	NRF24L01_TX_Mode();  // 设置为发送模式
	if(NRF24L01_TxPacket(NRF24L01_TX_BUF) == NRF24L01_TX_DS)
	{
		LED1(ON);
		Delay_ms(500);
		LED1(OFF);
	}
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
			ROCKER_COORDINATE(&Value);
			OLED_ShowString(1,1," Rocker Value !");
			OLED_ShowString(2,1,"LX:");
			OLED_ShowString(2,9,"RX:");
			OLED_ShowString(3,1,"LY:");
			OLED_ShowString(3,9,"RY:");
			OLED_ShowString(4,1,"Battery:");
			OLED_ShowNum(2,4,Value.ROCKER_LX_Value,3);
			OLED_ShowNum(2,12,Value.ROCKER_RX_Value,3);
			OLED_ShowNum(3,4,Value.ROCKER_LY_Value,3);
			OLED_ShowNum(3,12,Value.ROCKER_RY_Value,3);
			OLED_ShowNum(4,10,Value.Electricity,3);
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

