#ifndef __PWM_H__
#define __PWM_H__

#include <STC32G.H>

#define PWMA_Period			(20000 - 1)
#define PWMA_Prescaler		(24 - 1)

#define PWMB_Period			(100 - 1)
#define PWMB_Prescaler		(240 - 1)

void PWMA_Config();
void PWMB_Config();
void PWMB_SetCompare5(uint16_t Duty);
void PWMB_SetCompare6(uint16_t Duty);
void PWMA_SetCompare4(uint16_t Duty);

#endif /*__PWM_H__*/