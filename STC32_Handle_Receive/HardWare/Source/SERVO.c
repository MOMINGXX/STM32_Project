#include "SERVO.h"

uint8_t Servo_PWM = 3;

/****
	* @brief	舵机引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:SERVO_GPIO_Config();
    */
void SERVO_GPIO_Config()
{
	P1M1 &= ~0x80;
	P1M1 |= 0x80;		//P17 推挽输出
}

void Timer3_Init()		//500微秒@24.000MHz
{
	T4T3M |= 0x02;			//定时器时钟1T模式
	T3L = 0x20;				//设置定时初始值
	T3H = 0xD1;				//设置定时初始值
	T4T3M |= 0x08;			//定时器3开始计时
	ET3 = 1;
}

/****
	* @brief	舵机初始化 
	* @param   	无
	* @return   无 	
	* Sample usage:SERVO_Init();
    */
void SERVO_Init()
{
	SERVO_GPIO_Config();
	//PWMA_Config();
	Timer3_Init();
}

/****
	* @brief	舵机设置角度
	* @param   	Angle	设置角度
		@arg	0
		@arg	45
		@arg	90
		@arg	135
		@arg	180
	* @return   无 	
	* Sample usage:SERVO_Init();
    */
void SERVO_SetAngle(uint8_t Angle)
{
	PWMA_SetCompare4(Angle / 180 * 2000 + 500);
}

void Time3_Routine() interrupt 19
{
	static uint8_t Count;
	Count++;
	Count %= 40;
	if(Servo_PWM > Count)
	{
		Servo=1;
	}
	else 
	{
		Servo=0;
	}
}