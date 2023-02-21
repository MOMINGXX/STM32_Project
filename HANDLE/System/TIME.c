#include "TIME.h"

/****
	* @brief    定时器中断 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_NVIC_Config(); 
    */
static void TIMEx_NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStruct;
    //中断分组配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //参数配置
    NVIC_InitStruct.NVIC_IRQChannel = TIMEx_IRQChannel;      //中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;             //中断通道使能
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;          //子优先级
    NVIC_Init(&NVIC_InitStruct);
}

/****
	* @brief    定时器 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIMEx_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    //开启定时器时钟
    TIMEx_APBxClockCmd(TIMEx_CLK,ENABLE);
    //选择为内部时钟（默认内部时钟）
    TIM_InternalClockConfig(TIME_x);
    //参数配置
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //时钟分频 1分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //计数模式     向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;                   //ARR   自动重装
    TIM_TimeBaseInitStruct.TIM_Prescaler = 540 - 1;                 //PSC   预分频
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //重复计数器
    TIM_TimeBaseInit(TIME_x,&TIM_TimeBaseInitStruct);

    TIM_ClearFlag(TIME_x,TIM_IT_Update);

    TIM_ITConfig(TIME_x,TIM_IT_Update,ENABLE);      //定时器使能更新中断

    //使能定时器
    TIM_Cmd(TIME_x,ENABLE); 
}

/****
	* @brief    定时器 初始化		  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_Init(); 
    */
void TIMEx_Init()
{
    TIMEx_Config();
    TIMEx_NVIC_Config();
}


