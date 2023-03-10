#include "ULTRASONIC.h"

bit Flag = 0;

/****
	* @brief	超声波引脚配置    			  
	* @param   	无
	* @return   无    	
	* Sample usage:ULTRASONIC_GPIO_Config();
	* @note 
    */
static void ULTRASONIC_GPIO_Config()
{
	P0M1 &= ~0x04;
	P0M0 &= ~0x04;			//P02 为准双向口
	
	P3M1 &= ~0x08;
	P3M0 &= ~0x08;			//P33 为准双向口
}

/****
	* @brief	定时器1配置     			  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMER1_Config()();
	* @note 
    */
static void TIMER1_Config()		//24.000MHz
{
	AUXR |= 0x40;			//定时器时钟1T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0;				//设置定时初始值
	TH1 = 0;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
}

/****
	* @brief	超声波初始化      			  
	* @param   	无
	* @return   无    	
	* Sample usage:Ultrasonic_Init();
	* @note 
    */
void Ultrasonic_Init()
{
	Trig = 0;
	Echo = 0;
	ULTRASONIC_GPIO_Config();
	TIMER1_Config();	
}

/****
	* @brief	开启超声波     			  
	* @param   	无
	* @return   无    	
	* Sample usage:Ultrasonic_Start();
	* @note 
    */
static void Ultrasonic_Start()
{
	unsigned long i;
	Trig = 0;
	_nop_();
	Trig = 1;
	i = 58UL;
	while (i) i--;		//延时10us
	Trig = 0;
}

/****
	* @brief	超声波距离计算		  
	* @param   	无
	* @return   无    	
	* Sample usage:Ultrasonic_GetDistance();
    */
float Ultrasonic_GetDistance()
{
	uint8_t i = 0;
	uint16_t Time = 0;
	float Distance = 0;
	float Sum = 0;
	while(i != 5)
	{
		Ultrasonic_Start();
		Echo = 1;
		while(!Echo);		//等待低电平结束
		TR1 = 1;
		while(Echo);		//等待高电平结束
		TR1 = 0;
		i ++;
		Time = TH1*256+TL1;
		TH1=0;
		TL1=0;
		Distance = (float)Time * 0.0008;		//距离计算  cm
		Sum += Distance;
	}
	Distance = Sum / 5.0;
	return Distance;
}


