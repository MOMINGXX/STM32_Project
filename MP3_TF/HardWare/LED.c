#include "LED.h"

/****
	* @brief	LED��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage: Led_Init();
    */
void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//����ʱ��
	RCC_APB2PeriphClockCmd(LED_RCC_CMD,ENABLE);

	//����IO�˿�
	GPIO_InitStruct.GPIO_Pin=LED_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	��LED     			  
	* @param   	GPIOx		GPIO�˿�  x=A~G
	* @param   	GPIO_Pin	GPIO����  ��0~15��
	* @return   ��  	
	* Sample usage: Led_On(LED_GPIO_PORT,LED_GPIO_PIN);
    */
void Led_On(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

/****
	* @brief	�ر�LED     			  
	* @param   	GPIOx		GPIO�˿�  x=A~G
	* @param   	GPIO_Pin	GPIO����  ��0~15��
	* @return   ��  	
	* Sample usage: Led_Off(LED_GPIO_PORT,LED_GPIO_PIN);
    */
void Led_Off(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOx,GPIO_Pin);
}

