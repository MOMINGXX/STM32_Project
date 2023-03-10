#ifndef  _KEY_H_
#define	 _KEY_H_

#include <STC32G.H>
#include "BEEP.h"

sbit KEY1 = P0^4;
sbit KEY2 = P0^5;
sbit KEY3 = P0^6;

void KEY_Init();
uint8_t key();

#endif