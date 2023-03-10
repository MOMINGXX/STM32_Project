#include "NRFDATA.h"

void main()
{
	WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度
	
	//模块初始化
	Usartx_Init();
	NRF24L01_Init();
	MOTOR_Init();
	HC595_Init();
	KEY_Init();
	DHT11_GPIO_Config();
	Ultrasonic_Init();
	SERVO_Init();
	WS2812_GPIO_Config();
	
	
	HC595_SendData(0x00);					//LED灯全亮
	Uart_SendCMD(Specify_Volume,0,20);		//初始音量20
	
	EA = 1;		//开启总中断
	
	NRF24L01_Check_detection();		//检测NRF24L01 连接是否正常
	while(1)
	{
		Mode_Option();
	}
}

