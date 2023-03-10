#ifndef __BEEP_H__
#define __BEEP_H__

#include <STC32G.h>

sbit BEEP = P3^5;

void BEEP_GPIO_Config();

#endif      /* __BEEP_H__*/