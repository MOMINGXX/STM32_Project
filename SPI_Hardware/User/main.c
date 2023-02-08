#include "stm32f10x.h"                  // Device header
#include "GD25Q16.h"

uint8_t ReadBuff[256];
uint8_t WriteBuff[256];

int main()
{
	Usart_Init();
	GD25Q16_Init();

	printf("\r\nGD25Q16_ID:> 0x%x\r\n",GD25Q16_Read_JEDEC_ID()); 

	GD25Q16_Sector_Erase(0);
	
	for(int i = 0; i < 256; i++)
	{
		WriteBuff[i] = i;
	}
	GD25Q16_Page_Program(1,WriteBuff,256);
	
	GD25Q16_Read_Data(1,ReadBuff,256);

	for(int i = 0; i < 256; i++)
	{
		printf("0x%x\t",ReadBuff[i]); 
		if(i%10  == 0)
		{
			printf("\r\n");
		}
	}
	printf("\r\n");
	
	while(1)
	{
		
	}
} 

