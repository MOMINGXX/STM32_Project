#ifndef __NRFDATA_H__
#define __NRFDATA_H__

#include "NRF24L01.h"
#include "Delay.h"
#include "MOTOR.h"
#include "USART.h"
#include "SERVO.h"
#include "HC595.h"
#include "KEY.h"
#include "DHT11.h"
#include "WS2812.h"
#include "MP3_TF_16P.h"
#include "ULTRASONIC.h"

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

void Ws2812_Mode();
void Gravity_Mode();
void Bluetooth_Mode();
void Wireless_Mode();
void APP_ROCKER_Mode();
void APP_KEY_Mode();
void APP_MP3Play_Mode();
void Mode_Option();
void Rocker_Key_Mode();
void Key_Play_Mode();
void Avoid_Mode();

#endif	/*__NRFDATA_H__*/

