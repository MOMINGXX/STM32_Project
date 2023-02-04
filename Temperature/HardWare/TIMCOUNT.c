#include "TIMCOUNT.h"

/****
	* @brief	中断优先级配置    			  
	* @param   	无
	* @return   无  	
	* Sample usage:TIMx_NVIC_Config();
    */
static void TIMx_NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/****
	* @brief	定时器模式配置 			  
	* @param   	无
	* @return   无  	
	* Sample usage:TIMx_Mode_Config();
    * note:TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
    *      TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
    *      另外三个成员是通用定时器和高级定时器才有.
    */
static void TIMx_Mode_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    //开启定时器时钟
    GENERAL_TIM_APBxCMD(GENERAL_TIM_CLK,ENABLE);

    //配置定时器
    //时钟分频因子
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    //计算模式
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    //自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseInitStruct.TIM_Period = GENERAL_TIM_Period;
    //时钟预分频数
    TIM_TimeBaseInitStruct.TIM_Prescaler = GENERAL_TIM_Prescaler;
    //重复计数器的值
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    //初始化定时器
    TIM_TimeBaseInit(GENERAL_TIMx,&TIM_TimeBaseInitStruct);

    //清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIMx,TIM_FLAG_Update);

    //开启计数器中断
    TIM_ITConfig(GENERAL_TIMx,TIM_IT_Update,ENABLE);

    //使能计数器
    TIM_Cmd(GENERAL_TIMx,ENABLE);
}

/****
	* @brief	定时器初始化  			  
	* @param   	无
	* @return   无  	
	* Sample usage:TIMx_Init();
    */
void TIMx_Init()
{
    TIMx_NVIC_Config();
	TIMx_Mode_Config();	
    KEY_Init();
}

/****
	* @brief	定时器中断函数 	1ms		  
	* @param   	无
	* @return   无  	
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