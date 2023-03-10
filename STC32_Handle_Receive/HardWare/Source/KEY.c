#include "KEY.h"

uint8_t Key_KeyNum;

/****
	* @brief	按键引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:KEY_GPIO_Config();
    */
static void KEY_GPIO_Config()
{
	P0M0 &= ~0x70; 
	P0M1 &= ~0x70; 		//P04 P05 P06 为准双向口
}

/****
	* @brief	定时器0配置	 20ms / 24Mhz
	* @param   	无
	* @return   无 	
	* Sample usage:TIME0_Config();
    */
static void TIME0_Config()		
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0x63;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;            	//开启定时器中断
}

/****
	* @brief	按键初始化
	* @param   	无
	* @return   无 	
	* Sample usage:KEY_Init();
    */
void KEY_Init()
{
	KEY_GPIO_Config();
	BEEP_GPIO_Config();
	TIME0_Config();
}

/****
	* @brief	返回按键值
	* @param   	无
	* @return   Temp 	按键值	
	* Sample usage:key();
    */
uint8_t key()
{
	uint8_t Temp;
	Temp=Key_KeyNum;
	Key_KeyNum=0;
	return Temp;
}

/****
    * @brief	获取独立按键码
    * @param	无
    * @retval	按下按键的键码，范围：0~8，无按键按下时返回0
	* Sample usage:key_GetState();
    */
static uint8_t  key_GetState()
{
	uint8_t  keynumber=0;
	
	if(KEY1 == 0){keynumber=1;}
	if(KEY2 == 0){keynumber=2;}
	if(KEY3 == 0){keynumber=3;}
	
	return keynumber;
}	

/****
    * @brief	用于定时器每20ms检测是否有按键按下
    * @param	无
    * @retval	无
	* Sample usage:Key_Loop();
    */
static void Key_Loop()
{
	static uint8_t NowState,LastState;
	LastState=NowState;
	NowState=key_GetState();
	if(LastState==1 && NowState==0)
	{
		Key_KeyNum=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNum=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNum=3;
	}
}

/****
    * @brief	定时器中断函数 每20ms检测是否有按键按下
    * @param	无
    * @retval	无
    */
void Time0_Routine() interrupt 1
{
	Key_Loop();
}
