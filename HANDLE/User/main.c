#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MOTOR.h"

uint16_t i;

int main()
{
	OLED_Init();
	MOTOR_Init();
	OLED_ShowString(1,1,"MOTOR:");
	while(1)
	{
		MOTOR();
	}
}

