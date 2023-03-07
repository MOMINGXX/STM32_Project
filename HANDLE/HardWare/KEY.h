#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"                  // Device header
#include "NRF24L01.h"
#include "LED.h"
#include "TIME.h"
#include "Delay.h"

typedef enum 
{
    REDECE = 1,
    ADD,
    STOP,
    START,
    FORWWARD,
    LEFT,
    RIGHT,
    BACK,
    PLAY,
    SUSPENDED,
    NEXT,
    LAST,
}Key_Typedef;

#define KEYx_CLK                (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC)
#define KEY_APBx_ClockCMD       RCC_APB2PeriphClockCmd

#define KEY1x_GPIO_PORT         GPIOA       //x = 1,4,5,6,7,8,15
#define KEY2x_GPIO_PORT         GPIOB       //x = 10,11,12
#define KEY1_GPIO_PORT          GPIOC       

#define KEY1_GPIO_PIN           GPIO_Pin_13
#define KEY2_GPIO_PIN           GPIO_Pin_15
#define KEY3_GPIO_PIN           GPIO_Pin_1
#define KEY4_GPIO_PIN           GPIO_Pin_12
#define KEY5_GPIO_PIN           GPIO_Pin_5
#define KEY6_GPIO_PIN           GPIO_Pin_4
#define KEY7_GPIO_PIN           GPIO_Pin_6
#define KEY8_GPIO_PIN           GPIO_Pin_7
#define KEY9_GPIO_PIN           GPIO_Pin_10
#define KEY10_GPIO_PIN          GPIO_Pin_8
#define KEY11_GPIO_PIN          GPIO_Pin_11

void KEY_Init();
void KEY_LOOP();
uint8_t KEY_GetNumber();
uint8_t Key_GetNumber();
void Key_Send(uint8_t KetNum);
                                
#endif                          
