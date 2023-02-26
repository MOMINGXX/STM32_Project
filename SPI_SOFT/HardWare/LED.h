#ifndef	__LED_H__
#define __LED_H__

#include "stm32f10x.h"                  // Device header

#define LED_GPIO_PIN    GPIO_Pin_All
#define LED_GPIO_PORT   GPIOB
#define LED_RCC_CMD     RCC_APB2Periph_GPIOB

#define ON          1
#define OFF         0

#define LED(x)  if(x) \
                    GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN); \
                else \
                    GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);

#define LED_TOGGLE (LED_GPIO_PORT->ODR ^= LED_GPIO_PIN)

void Led_Init(void);
void Led_On(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void Led_Off(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif	/*__LED_H__*/

