#include "stm32f10x.h"                  // Device header
#include "Deal.h"

int main()
{
	Deal_Init();
	while(1)
	{
		Key_Get();
		Temp_Alarm();
	}
} 

