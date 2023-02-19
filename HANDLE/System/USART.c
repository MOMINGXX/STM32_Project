#include "Time.h"

/****
	* @brief    ��ʱ�� ����			  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIME3_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
    //������ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    //��������
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //ʱ�ӷ�Ƶ 1��Ƶ
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //����ģʽ     ���ϼ���
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                  //ARR   �Զ���װ
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36 - 1;                	//PSC   Ԥ��Ƶ		
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //�ظ�������
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
    //��������
    TIM_OCStructInit(&TIM_OCInitStruct);                            //��ʼ���ṹ��
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //PWM1 ģʽ 
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //�������
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;      //���״̬ʹ��
    TIM_OCInitStruct.TIM_Pulse = 0;                     			//CCR
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM3,ENABLE); 
}

/****
	* @brief    ��ʱ�� ����			  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIME4_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
    //������ʱ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    //��������
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //ʱ�ӷ�Ƶ 1��Ƶ
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //����ģʽ     ���ϼ���
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                  //ARR   �Զ���װ
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36 - 1;                	//PSC   Ԥ��Ƶ		
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //�ظ�������
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
    //��������
    TIM_OCStructInit(&TIM_OCInitStruct);                            //��ʼ���ṹ��
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //PWM1 ģʽ 
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //�������
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;      //���״̬ʹ��
    TIM_OCInitStruct.TIM_Pulse = 0;                     			//CCR
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);

    //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE); 
}


/****
	* @brief    ��ʱ�� ��ʼ��		  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_Init(); 
    */
void TIMEx_Init()
{
    TIME3_Config();
    TIME4_Config();
}

