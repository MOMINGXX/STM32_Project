#include "LED.h"

/****
	* @brief    LED 引脚 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:LED_Config(); 
    */
static void LED_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //开启GPIO时钟
    LED_APBxClockCMD(LEDx_CLK,ENABLE);

    //参数配置
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN | LED3_GPIO_PIN;
    GPIO_Init(LEDx_GPIO_PORT,&GPIO_InitStruct);
	
	LED1(OFF);
	LED2(OFF);
	LED3(OFF);
}

/****
	* @brief    LED 初始化			  
	* @param   	无
	* @return   无    	
	* Sample usage:LED_Init(); 
    */
void LED_Init()
{
    LED_Config();
}

