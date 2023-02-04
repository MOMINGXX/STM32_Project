#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"                  // Device header

#define LED_GPIO_PORT           GPIOB
#define LED_GPIO_CLK            RCC_APB2Periph_GPIOB
#define LED_GPIO_APBxCMD        RCC_APB2PeriphClockCmd

#define LED1_GPIO_PIN           GPIO_Pin_3   
#define LED2_GPIO_PIN           GPIO_Pin_5
#define LED3_GPIO_PIN           GPIO_Pin_6
#define LED4_GPIO_PIN           GPIO_Pin_7
#define LED5_GPIO_PIN           GPIO_Pin_8
#define LED6_GPIO_PIN           GPIO_Pin_9
//#define ALL_LED_GPIO_PIN        (LED1_GPIO_PIN | LED2_GPIO_PIN | LED3_GPIO_PIN | \
                                 LED4_GPIO_PIN | LED5_GPIO_PIN | LED6_GPIO_PIN)
#define ALL_LED_GPIO_PIN        ((uint16_t)0x03E0)

typedef enum
{
    OFF,
    ON
}LED_Mode;                                

#define LED1_ON                 GPIO_ResetBits(LED_GPIO_PORT,LED1_GPIO_PIN);   
#define LED1_OFF                GPIO_SetBits(LED_GPIO_PORT,LED1_GPIO_PIN); 

#define LED1(Status)            if(Status) \
                                    GPIO_ResetBits(LED_GPIO_PORT,LED1_GPIO_PIN); \
                                else \
                                    GPIO_SetBits(LED_GPIO_PORT,LED1_GPIO_PIN); 

#define LED_TOGGLE(PORT,PIN)    (PORT->ODR ^= PIN)         

 void LED_Init();
 void LED_On(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
 void LED_Off(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin); 
 void LED_Control(LED_Mode Status,uint16_t GPIO_Pin);                           

#endif  /*__LED_H__*/
