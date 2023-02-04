#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"                  // Device header

#define KEY_GPIO_PORT               GPIOA
#define KEY_GPIO_CLK                RCC_APB2Periph_GPIOA
#define KEY_GPIO_APBxCMD            RCC_APB2PeriphClockCmd

//#define KEY_GPIO_PIN                ((uint16_t)0x00FF)
#define KEY_GPIO_PIN            (KEY1_GPIO_PIN | KEY2_GPIO_PIN | KEY3_GPIO_PIN | KEY4_GPIO_PIN | \
                                     KEY5_GPIO_PIN | KEY6_GPIO_PIN | KEY7_GPIO_PIN | KEY8_GPIO_PIN)

#define KEY1_GPIO_PIN               GPIO_Pin_0
#define KEY2_GPIO_PIN               GPIO_Pin_1
#define KEY3_GPIO_PIN               GPIO_Pin_2
#define KEY4_GPIO_PIN               GPIO_Pin_3
#define KEY5_GPIO_PIN               GPIO_Pin_4
#define KEY6_GPIO_PIN               GPIO_Pin_5
#define KEY7_GPIO_PIN               GPIO_Pin_6
#define KEY8_GPIO_PIN               GPIO_Pin_7

#define KEY_R_STATUS(PORT,PIN)      GPIO_ReadInputDataBit(PORT,PIN)

void KEY_Init();
uint8_t KEY_GetNumber();
void KEY_Loop();

#endif  /*__KEY_H__*/
