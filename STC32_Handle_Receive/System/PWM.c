#include "PWM.h"

/****
	* @brief	PWMB配置	  电机PWM
	* @param   	无
	* @return   无 	
	* Sample usage:PWMB_Config();
    */
void PWMB_Config()
{
	PWMB_PS = 0x00;			//选择通道5 P20   通道6 P21
	
	PWMB_CCER1 = 0x00;		//比较使能寄存器		清零
	PWMB_CCMR1 = 0x60;		//比较模式寄存器		PWM模式1 向上计数
	PWMB_CCMR2 = 0x60;		//比较模式寄存器		PWM模式1 向上计数
	PWMB_CCER1 = 0x11;		//比较使能寄存器		开启比较输出 输出高电平
	
	PWMB_PSCRH = (uint8_t)(PWMB_Prescaler >> 8);	//预分频器高8位
	PWMB_PSCRL = (uint8_t)PWMB_Prescaler;			//预分频器低8位
	PWMB_ARRH = (uint8_t)(PWMB_Period >> 8);		//自动重装载寄存器高8位
	PWMB_ARRL = (uint8_t)PWMB_Period	;			//自动重装载寄存器低8位
	PWMB_CCR5H = 0;		//比较寄存器高8位
	PWMB_CCR5L = 0;		//比较寄存器低8位
	PWMB_CCR6H = 0;		//比较寄存器高8位
	PWMB_CCR6L = 0;		//比较寄存器低8位
	
	PWMB_ENO = 0x05;		//输出使能寄存器		使能PWM5 PWM6输出
	PWMB_BKR = 0x80;		//输出主使能
	PWMB_CR1 = 0x01;		//控制寄存器 使能计数
}

/****
	* @brief	PWMA配置	舵机PWM	  
	* @param   	无
	* @return   无 	
	* Sample usage:PWMA_Config();
    */
void PWMA_Config()
{
	PWMA_PS = 0x00;			//选择通道4 P16 P17
	
	PWMA_CCER2 = 0x00;		//比较使能寄存器		清零
	PWMA_CCMR4 = 0x60;		//比较模式寄存器		PWM模式1 向上计数
	PWMA_CCER2 = 0x40;		//比较使能寄存器		开启比较输出 输出高电平
	
	PWMA_PSCRH = (uint8_t)(PWMA_Prescaler >> 8);	//预分频器高8位
	PWMA_PSCRL = (uint8_t)PWMA_Prescaler;			//预分频器低8位
	PWMA_ARRH = (uint8_t)(PWMA_Period >> 8);		//自动重装载寄存器高8位
	PWMA_ARRL = (uint8_t)PWMA_Period	;			//自动重装载寄存器低8位
	PWMA_CCR4H = 0;		//比较寄存器高8位
	PWMA_CCR4L = 0;		//比较寄存器低8位
	
	PWMA_ENO = 0x80;		//输出使能寄存器		使能PWM5 PWM6输出
	PWMA_BKR = 0x80;		//输出主使能
	PWMA_CR1 = 0x01;		//控制寄存器 使能计数
}

/****
	* @brief	PWMB 通道5 占空比设置
	* @param   	Duty	设置的占空比 
	* @return   无 	
	* Sample usage:PWMB_SetCompare5(100);
    */
void PWMB_SetCompare5(uint16_t Duty)
{
	PWMB_CCR5H = (uint8_t)(Duty >> 8);	//比较寄存器高8位	占空比
	PWMB_CCR5L = (uint8_t)Duty;			//比较寄存器低8位
}

/****
	* @brief	PWMB 通道6 占空比设置
	* @param   	Duty	设置的占空比 
	* @return   无 	
	* Sample usage:PWMB_SetCompare5(100);
    */
void PWMB_SetCompare6(uint16_t Duty)
{
	PWMB_CCR6H = (uint8_t)(Duty >> 8);	//比较寄存器高8位	占空比
	PWMB_CCR6L = (uint8_t)Duty;			//比较寄存器低8位
}

/****
	* @brief	PWMA 通道4 占空比设置
	* @param   	Duty	设置的占空比 
	* @return   无 	
	* Sample usage:PWMA_SetCompare5(100);
    */
void PWMA_SetCompare4(uint16_t Duty)
{
	PWMA_CCR4H = (uint8_t)(Duty >> 8);	//比较寄存器高8位	占空比
	PWMA_CCR4L = (uint8_t)Duty;			//比较寄存器低8位
}