#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "RainDrop_Module.h"
#include "Delay.h"

extern __IO uint16_t Rain_size;
float Volatge;

int main()
{
	Usart_Init();
	Led_Init();
	RainDrop_Init();
	Led_Off(LED_GPIO_PORT,LED_GPIO_PIN);
	while(1)
	{
		RainDrop_Detect();
		Volatge = (float)Rain_size/4095*3.3;
		printf("Volatge:%f\n",Volatge);
		Delay_s(1);
	}
} 

