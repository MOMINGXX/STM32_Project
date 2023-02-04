#include "TIMCOUNT.h"

/****
	* @brief	�ж����ȼ�����    			  
	* @param   	��
	* @return   ��  	
	* Sample usage:TIMx_NVIC_Config();
    */
static void TIMx_NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/****
	* @brief	��ʱ��ģʽ���� 			  
	* @param   	��
	* @return   ��  	
	* Sample usage:TIMx_Mode_Config();
    * note:TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
    *      TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
    *      ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
    */
static void TIMx_Mode_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    //������ʱ��ʱ��
    GENERAL_TIM_APBxCMD(GENERAL_TIM_CLK,ENABLE);

    //���ö�ʱ��
    //ʱ�ӷ�Ƶ����
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    //����ģʽ
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    //�Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseInitStruct.TIM_Period = GENERAL_TIM_Period;
    //ʱ��Ԥ��Ƶ��
    TIM_TimeBaseInitStruct.TIM_Prescaler = GENERAL_TIM_Prescaler;
    //�ظ���������ֵ
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    //��ʼ����ʱ��
    TIM_TimeBaseInit(GENERAL_TIMx,&TIM_TimeBaseInitStruct);

    //����������жϱ�־λ
    TIM_ClearFlag(GENERAL_TIMx,TIM_FLAG_Update);

    //�����������ж�
    TIM_ITConfig(GENERAL_TIMx,TIM_IT_Update,ENABLE);

    //ʹ�ܼ�����
    TIM_Cmd(GENERAL_TIMx,ENABLE);
}

/****
	* @brief	��ʱ����ʼ��  			  
	* @param   	��
	* @return   ��  	
	* Sample usage:TIMx_Init();
    */
void TIMx_Init()
{
    TIMx_NVIC_Config();
	TIMx_Mode_Config();	
    KEY_Init();
}

/****
	* @brief	��ʱ���жϺ��� 	1ms		  
	* @param   	��
	* @return   ��  	
    */
void GENERAL_TIM_IRQHandler()
{
    static uint8_t count = 0;
    if(RESET != TIM_GetITStatus(GENERAL_TIMx,TIM_IT_Update))
    {
        count++;
		count %= 20;
        KEY_Loop();
//        if(count == 20)
//        {
//            count = 0;
//            KEY_Loop();
//        }
        TIM_ClearITPendingBit(GENERAL_TIMx,TIM_IT_Update);
    }
}