#include "BEEP.h"

/****
	* @brief	BEEP рЩ╫ееДжц	  
	* @param   	нч
	* @return   нч 	
	* Sample usage:BEEP_GPIO_Config()();
    */
void BEEP_GPIO_Config()
{
	P3M1 &= ~0x20;
	P3M0 &= ~0x20;
}