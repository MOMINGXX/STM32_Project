#include "MOTOR.h"

/****
	* @brief	电机引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:MOTOR_GPIO_Config();
    */
void MOTOR_GPIO_Config()
{
	P2M1 &= ~0xCF;
    P2M0 |= 0xCF;		//P20 P21 P22 P23 P26 P27 推挽输出
}

/****
	* @brief	电机初始化 
	* @param   	无
	* @return   无 	
	* Sample usage:MOTOR_Init();
    */
void MOTOR_Init()
{
    MOTOR_GPIO_Config();
	PWMB_Config();
}

/****
    * @brief	前进
    * @param	无
    * @retval	无
	* Sample usage:MOTOR_ForWard();
	*/
void MOTOR_ForWard()
{
	Left_moto_go;
	Right_moto_go ;	
}

/****
    *@brief		回退
    *@param		无
    *@retval	无
	* Sample usage:MOTOR_BackWard();
*****/
void MOTOR_BackWard()
{
	Left_moto_back;
	Right_moto_back;
}

/****
    * @brief	左转
    * @param	无
    * @retval	无
	* Sample usage:
	*/
void MOTOR_TurnLeft()
{
	Left_moto_back;
	Right_moto_go;
}

/****
    * @brief	右转
    * @param	无
    * @retval	无
	* Sample usage:MOTOR_Turnright();
	*/
void MOTOR_Turnright()
{
	Right_moto_back;
	Left_moto_go;
}

/****
    * @brief	停止
    * @param	无
    * @retval	无
	* Sample usage:MOTOR_Stop();
	*/
void MOTOR_Stop()
{
	Right_moto_Stop;
	Left_moto_Stop;
}

