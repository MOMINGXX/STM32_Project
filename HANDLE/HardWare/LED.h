#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"                  // Device header

#define LEDx_CLK				(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC)
#define LED_APBxClockCMD		RCC_APB2PeriphClockCmd

#define LED1_GPIO_PORT          GPIOB
#define LEDx_GPIO_PORT          GPIOC
#define LED1_GPIO_PIN           GPIO_Pin_3
#define LED2_GPIO_PIN           GPIO_Pin_14
#define LED3_GPIO_PIN           GPIO_Pin_15

#define ON                      1
#define OFF                     0

#define LED1(x)                 if(x) \
									GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN); \
								else \
									GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
#define LED2(x)                 if(x) \
									GPIO_ResetBits(LEDx_GPIO_PORT,LED2_GPIO_PIN); \
								else \
									GPIO_SetBits(LEDx_GPIO_PORT,LED2_GPIO_PIN);								
#define LED3(x)                 if(x) \
									GPIO_ResetBits(LEDx_GPIO_PORT,LED3_GPIO_PIN); \
								else \
									GPIO_SetBits(LEDx_GPIO_PORT,LED3_GPIO_PIN);
#define LED1_TOGGLE				(LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN)					
								
void LED_Init();

#endif
