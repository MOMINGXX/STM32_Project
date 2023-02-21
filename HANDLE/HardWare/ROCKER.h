#ifndef __ROCKER_H__
#define __ROCKER_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define NUMCHANNEL          5

//ADC
#define ROCKER_ADCx                         ADC1
#define ROCKER_ADCx_CLK                     RCC_APB2Periph_ADC1
#define ROCKER_ADCx_APBxClockCMD            RCC_APB2PeriphClockCmd
#define ROCKER_ADCx_Channel1                ADC_Channel_2
#define ROCKER_ADCx_Channel2                ADC_Channel_3
#define ROCKER_ADCx_Channel3                ADC_Channel_8
#define ROCKER_ADCx_Channel4                ADC_Channel_9
#define ROCKER_ADCx_Channel5                ADC_Channel_0

//DMA
#define ROCKER_DMAx_CLK                     RCC_AHBPeriph_DMA1 
#define ROCKER_DMAx_APBxClockCMD            RCC_AHBPeriphClockCmd
#define ROCKER_DMAX_Channel                 DMA1_Channel1

//GPIO
#define ROCKER_ADCLx_GPIO_CLK               RCC_APB2Periph_GPIOA
#define ROCKER_ADCLx_GPIO_APBxClockCMD      RCC_APB2PeriphClockCmd
#define ROCKER_ADCLx_GPIO_PORT              GPIOA
#define ROCKER_ADCL1x_GPIO_PIN              GPIO_Pin_2
#define ROCKER_ADCL2x_GPIO_PIN              GPIO_Pin_3
#define ROCKER_ADCR3x_GPIO_PIN              GPIO_Pin_0

#define ROCKER_ADCRx_GPIO_CLK               RCC_APB2Periph_GPIOB
#define ROCKER_ADCRx_GPIO_APBxClockCMD      RCC_APB2PeriphClockCmd
#define ROCKER_ADCRx_GPIO_PORT              GPIOB
#define ROCKER_ADCR1x_GPIO_PIN              GPIO_Pin_0
#define ROCKER_ADCR2x_GPIO_PIN              GPIO_Pin_1

void AD_GetValue();
void ROCKER_Init();

#endif
