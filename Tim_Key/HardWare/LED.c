#include "LED.h"

/****
	* @brief	LED��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage: Led_Init();
    */
void LED_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //GPIOʱ��ʹ��
    LED_GPIO_APBxCMD(LED_GPIO_CLK,ENABLE);

    //GPIO����
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN | LED2_GPIO_PIN | LED3_GPIO_PIN |
                               LED4_GPIO_PIN | LED5_GPIO_PIN | LED6_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	��LED     			  
	* @param   	GPIOx		GPIO�˿�  x=A~G
	* @param   	GPIO_Pin	GPIO����  ��0~15��
	* @return   ��  	
	* Sample usage: Led_On(LED_GPIO_PORT,LED_GPIO_PIN);
    */
void LED_On(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
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
void LED_Off(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
    GPIO_SetBits(GPIOx,GPIO_Pin);
}

/****
	* @brief	�ر�LED     			  
	* @param   	Status      LED ״̬ ��/��
	* @param   	GPIO_Pin	GPIO����  ��0~15��
	* @return   ��  	
	* Sample usage:LED_Control(ON,LED_GPIO_PIN);
    */
void LED_Control(LED_Mode Status,uint16_t GPIO_Pin)
{
    if(Status)
    {
        LED_On(LED_GPIO_PORT,GPIO_Pin);
    }
    else
    {
        LED_Off(LED_GPIO_PORT,GPIO_Pin);
    }
}