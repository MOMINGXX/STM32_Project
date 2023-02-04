#include "KEY.h"

uint8_t KeyNumber;

/****
	* @brief	KEY 初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage:KEY_Init();
    */
void KEY_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //GPIO时钟使能
    KEY_GPIO_APBxCMD(KEY_GPIO_CLK,ENABLE);

    //GPIO配置
    GPIO_InitStruct.GPIO_Pin = KEY_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_GPIO_PORT,&GPIO_InitStruct);
}

uint8_t KEY_GetNumber()
{
	uint8_t Temp;
	Temp=KeyNumber;
	KeyNumber=0;
	return Temp;
}

static uint8_t KEY_ReadNumber()
{
	uint8_t Number=0;
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY1_GPIO_PIN)==RESET)	{Number=1;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY2_GPIO_PIN)==RESET)	{Number=2;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY3_GPIO_PIN)==RESET)	{Number=3;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY4_GPIO_PIN)==RESET)	{Number=4;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY5_GPIO_PIN)==RESET)	{Number=5;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY6_GPIO_PIN)==RESET)	{Number=6;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY7_GPIO_PIN)==RESET)	{Number=7;}
	if(KEY_R_STATUS(KEY_GPIO_PORT,KEY8_GPIO_PIN)==RESET)	{Number=8;}
	return Number;
}

void KEY_Loop()
{
	static uint8_t NowState,LastState;
	LastState=NowState;
	NowState=KEY_ReadNumber();
	if(LastState==1 && NowState==0)	{KeyNumber=1;}
	if(LastState==2 && NowState==0)	{KeyNumber=2;}
	if(LastState==3 && NowState==0)	{KeyNumber=3;}
	if(LastState==4 && NowState==0)	{KeyNumber=4;}
	if(LastState==5 && NowState==0)	{KeyNumber=5;}
	if(LastState==6 && NowState==0)	{KeyNumber=6;}
	if(LastState==7 && NowState==0)	{KeyNumber=7;}
	if(LastState==8 && NowState==0)	{KeyNumber=8;}
}