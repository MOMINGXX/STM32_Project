#include "LED.h"

/****
	* @brief	LED初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage: Led_Init();
    */
void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开启时钟
	RCC_APB2PeriphClockCmd(LED_RCC_CMD,ENABLE);

	//配置IO端口
	GPIO_InitStruct.GPIO_Pin=LED_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	打开LED     			  
	* @param   	GPIOx		GPIO端口  x=A~G
	* @param   	GPIO_Pin	GPIO引脚  （0~15）
	* @return   无  	
	* Sample usage: Led_On(LED_GPIO_PORT,LED_GPIO_PIN);
    */
void Led_On(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

/****
	* @brief	关闭LED     			  
	* @param   	GPIOx		GPIO端口  x=A~G
	* @param   	GPIO_Pin	GPIO引脚  （0~15）
	* @return   无  	
	* Sample usage: Led_Off(LED_GPIO_PORT,LED_GPIO_PIN);
    */
void Led_Off(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOx,GPIO_Pin);
}

