#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "LED.h"
#include "Delay.h"
#include "TIMCOUNT.h"

uint32_t i = 0, j= 0;
uint8_t KEYNUM;

int main()
{
	OLED_Init();
	LED_Init();
	TIMx_Init();
	LED_Off(LED_GPIO_PORT,ALL_LED_GPIO_PIN);
	OLED_ShowString(1,4,"OLED Test !");
	while(1)
	{
		KEYNUM = KEY_GetNumber();
		i++;
		i %= 65536;
		Delay_ms(1000);
		OLED_ShowNum(2,1,i,5);
		
		if(KEYNUM == 1)
		{
			LED_TOGGLE(LED_GPIO_PORT,ALL_LED_GPIO_PIN);
		}
		else if(KEYNUM == 2)
		{
			j++;
		}
		OLED_ShowNum(3,1,j,5);
	}
}

