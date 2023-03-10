#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include <STC32G.H>

sbit Trig = P0^2;
sbit Echo = P3^3;

void Ultrasonic_Init();
float Ultrasonic_GetDistance();

#endif /*__ULTRASONIC_H__*/