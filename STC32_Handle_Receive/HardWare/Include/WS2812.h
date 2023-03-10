#ifndef __WS2812_H__
#define __WS2812_H__

#include <STC32G.H>
#include <stdlib.h>
#include "Delay.h"

sbit WS2812_PIN = P5^3;

extern float RGB_R,RGB_G,RGB_B;

void WS2812_GPIO_Config();
void Rainbow(uint16_t wait);
void RainbowCycle(uint16_t wait) ;
void WS2812_RGB_Reset();
void WS2812_RGB_White(uint8_t Num);
void WS2812_RGB_Red(uint8_t Num);
void WS2812_RGB_Green(uint8_t Num);
void WS2812_RGB_Blue(uint8_t Num);
void RGB_RandomColor(uint8_t Num);
void TheaterChaseRainbow(uint16_t wait); 
void SetPixelColor(uint8_t num,uint32_t c);
void TheaterChase(uint32_t c, uint16_t wait) ;
void hsv_to_rgb(int h,int s,int v,float *R,float *G,float *B);
void WS2812_RGB_SetColor(uint8_t green,uint8_t red,uint8_t blue);
unsigned long Color(unsigned char r, unsigned char g, unsigned char b);

#endif   /* __WS2812_H__*/