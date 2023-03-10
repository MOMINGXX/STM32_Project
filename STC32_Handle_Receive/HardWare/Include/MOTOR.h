#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <STC32G.H>
#include "PWM.h"

//定义驱动器使能端引脚
sbit L298N_ENA = P2^0;
sbit L298N_ENB = P2^1;

//定义驱动器输出端引脚
sbit L298N_IN1 = P2^2;
sbit L298N_IN2 = P2^3;
sbit L298N_IN3 = P2^6;
sbit L298N_IN4 = P2^7;

#define Left_moto_go      {L298N_IN1=1,L298N_IN2=0;}  		//左电机向前走
#define Left_moto_back    {L298N_IN1=0,L298N_IN2=1;} 		//左边电机向后转
#define Left_moto_Stop    {L298N_IN1=0,L298N_IN2=0;}        //左边电机停转                     
#define Right_moto_go     {L298N_IN3=1,L298N_IN4=0;}		//右边电机向前走
#define Right_moto_back   {L298N_IN3=0,L298N_IN4=1;}		//右边电机向后走
#define Right_moto_Stop   {L298N_IN3=0,L298N_IN4=0;}      	//右边电机停转 

void MOTOR_Init();
void MOTOR_ForWard();
void MOTOR_BackWard();
void MOTOR_TurnLeft();
void MOTOR_Turnright();
void MOTOR_Stop();

#endif /*__MOTOR_H__*/