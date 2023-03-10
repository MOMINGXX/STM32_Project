#ifndef  __DuoJi_H__
#define  __DuoJi_H__

#include <STC32G.h>
#include "PWM.h"

extern uint8_t Servo_PWM;

void SERVO_Init();
void SERVO_SetAngle(uint8_t Angle);

sbit Servo = P5^2;

#endif