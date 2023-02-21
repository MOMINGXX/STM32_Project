#ifndef __TIME_H__
#define __TIME_H__

#include "stm32f10x.h"                  // Device header

#define TIME_x                      TIM2
#define TIMEx_CLK                   RCC_APB1Periph_TIM2
#define TIMEx_APBxClockCmd          RCC_APB1PeriphClockCmd

#define TIMEx_IRQChannel            TIM2_IRQn
#define TIMEx_IRQHandler            TIM2_IRQHandler

void TIMEx_Init();

#endif /*__TIME_H__*/

