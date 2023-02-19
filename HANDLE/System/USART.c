#include "Time.h"

/****
	* @brief    定时器 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIME3_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
    //开启定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    //参数配置
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //时钟分频 1分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //计数模式     向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                  //ARR   自动重装
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36 - 1;                	//PSC   预分频		
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //重复计数器
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
    //参数配置
    TIM_OCStructInit(&TIM_OCInitStruct);                            //初始化结构体
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //PWM1 模式 
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //输出极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;      //输出状态使能
    TIM_OCInitStruct.TIM_Pulse = 0;                     			//CCR
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);

    //使能定时器
    TIM_Cmd(TIM3,ENABLE); 
}

/****
	* @brief    定时器 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIME4_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
    //开启定时器时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    //参数配置
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //时钟分频 1分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //计数模式     向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                  //ARR   自动重装
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36 - 1;                	//PSC   预分频		
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //重复计数器
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
    //参数配置
    TIM_OCStructInit(&TIM_OCInitStruct);                            //初始化结构体
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //PWM1 模式 
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //输出极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;      //输出状态使能
    TIM_OCInitStruct.TIM_Pulse = 0;                     			//CCR
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);

    //使能定时器
	TIM_Cmd(TIM4,ENABLE); 
}


/****
	* @brief    定时器 初始化		  
	* @param   	无
	* @return   无    	
	* Sample usage:TIMEx_Init(); 
    */
void TIMEx_Init()
{
    TIME3_Config();
    TIME4_Config();
}

