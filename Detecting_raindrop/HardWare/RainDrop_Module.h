#ifndef	__RainDrop_Module_H__
#define __RainDrop_Module_H__

#include "stm32f10x.h"                  // Device header
#include "LED.h"

//ADC
#define RAINDROP_ADCx                   ADC1
#define RAINDROP_ADC_CLK                RCC_APB2Periph_ADC1
#define RAINDROP_ADC_APBxCLKCMD         RCC_APB2PeriphClockCmd
#define RAINDROP_ADC_Channel            ADC_Channel_1

//DMA
#define RAINDROP_DMA_CLK                RCC_AHBPeriph_DMA1
#define RAINDROP_DMA_AHBxCLKCMD         RCC_AHBPeriphClockCmd
#define RAINDROP_DMA_Channel            DMA1_Channel1

//GPIO
#define RAINDROP_AO_CLK                 RCC_APB2Periph_GPIOA
#define RAINDROP_DO_CLK    			    RCC_APB2Periph_GPIOA
#define RAINDROP_APBxCLKCMD			    RCC_APB2PeriphClockCmd

#define RAINDROP_AO_GPIO_PIN		    GPIO_Pin_1
#define RAINDROP_AO_GPIO_PORT		    GPIOA
#define RAINDROP_DO_GPIO_PIN		    GPIO_Pin_0
#define RAINDROP_DO_GPIO_PORT		    GPIOA

void RainDrop_Init();
void RainDrop_Detect();

#endif	/*__RainDrop_Module_H__*/

