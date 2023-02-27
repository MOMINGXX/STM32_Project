#ifndef __ROCKER_H__
#define __ROCKER_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

typedef struct 
{
    uint16_t ROCKER_RX_Value;
    uint16_t ROCKER_RY_Value;
    uint16_t ROCKER_LX_Value;
    uint16_t ROCKER_LY_Value;
    float Electricity;
}ROCKER_Value;

#define Y_ADC_MIN 0
#define Y_COORDINATE_MIN 0
#define Y_COORDINATE_MAX 100

// 定义电池额定电压
#define BATTERY_RATED_VOLTAGE 3.7f
// 定义ADC分辨率
#define ADC_RESOLUTION 4096

//通道数目
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

void ROCKER_Init();
void ROCKER_COORDINATE(ROCKER_Value *Value);

#endif
