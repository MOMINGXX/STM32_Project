#include "stm32f10x.h"                  // Device header
#include "MP3_TF_16P.h"

int main()
{
	Usart_Init();
	Uart_SendCMD(Specify_Volume ,0x00,20);
	Uart_SendFolder(Specify_Folder,0x00,2,6);
	while(1)
	{
		
	}
} 

