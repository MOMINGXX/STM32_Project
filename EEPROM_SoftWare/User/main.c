#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "LED.h"
#include "EEPROM.h"

uint8_t arr1[256]={0};
uint8_t arr2;
uint8_t arr3[256]={0};

int main()
{
	Usart_Init();
	EEPROM_Init();

	
	for(int i = 0; i < 256; i ++)
	{
		arr1[i] = i;
	}
	EEPROM_Page_Write(0,arr1,255);
	Delay_ms(10);
	EEPROM_Sequential_Read(0,arr3,255);
	for(int i = 0; i < 256; i ++)
	{
		printf("0x%x ",arr3[i]);
	}

	while(1)
	{
		
	}
} 

