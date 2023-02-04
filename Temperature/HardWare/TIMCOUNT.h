#ifndef __TIMCOUNT_H__
#define __TIMCOUNT_H__

#include "stm32f10x.h"                  // Device header
#include "KEY.h"

#define GENERAL_TIM2        1              
#define GENERAL_TIM3        0     

#if GENERAL_TIM2
#define GENERAL_TIMx                TIM2
#define GENERAL_TIM_CLK             RCC_APB1Periph_TIM2
#define GENERAL_TIM_APBxCMD         RCC_APB1PeriphClockCmd
#define GENERAL_TIM_Period          (1000-1)
#define GENERAL_TIM_Prescaler       71
#define GENERAL_TIM_IRQ             TIM2_IRQn
#define GENERAL_TIM_IRQHandler      TIM2_IRQHandler

#elif GENERAL_TIM3

#define GENERAL_TIMx                TIM3
#define GENERAL_TIM_CLK             RCC_APB1Periph_TIM3
#define GENERAL_TIM_APBxCMD         RCC_APB1PeriphClockCmd
#define GENERAL_TIM_Period          (1000-1)
#define GENERAL_TIM_Prescaler       71
#define GENERAL_TIM_IRQ             TIM3_IRQn
#define GENERAL_TIM_IRQHandler      TIM3_IRQHandler

#endif

void TIMx_Init();

#endif /*__TIMCOUNT_H__*/
