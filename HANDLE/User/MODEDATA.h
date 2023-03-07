#ifndef __MODEDATA_H__
#define __MODEDATA_H__

#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "LED.h"
#include "nmswj.h"
#include "KEY.h"
#include "MPU6050.h"
#include "ROCKER.h"
#include "NRF24L01.h"

typedef enum
{
    BLUETOOTH_MODE = 1,
    ROCKER_MODE,
    PLAY_MODE,
    GRAVITY_MODE,
    KEY_MODE,
    AVOID_MODE,
    WS2812_MODE
}Mode_Init;

#define DETERMIN    9
#define RETURN      5

void KEY_SCAN();
void OLED_Mode(Mode_Init Mode);
void Mode_Option();

#endif /* __MODEDATA_H__*/


