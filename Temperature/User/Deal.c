#include "Deal.h"

uint8_t TempH,TempL,HumiH,HumiL;
float T;

void Deal_Init()
{
    Usart_Init();
	DS18B20_CLK_ENABLE;
	DHT11_CLK_ENABLE;
    //EEPROM_Init();
	OLED_Init();

    OLED_ShowString(1,1,"Temp Humi Test!");
}

void OLED_DS18B20_Temp()
{
	OLED_ShowString(2,1,"Temp:");
	OLED_ShowChar(2,13,'¡æ');
	DS18B20_ConvertT();
	T=DS18B20_ReadT();
	printf("\r\nwd:>%f\n",T);
	if(T<0)
	{
        OLED_ShowNum(2,7,T,3);
        OLED_ShowNum(2,11,(uint32_t)(T*10000)%10000,2);
		OLED_ShowChar(2,10,'.');
		OLED_ShowChar(2,6,'-');
	}
	OLED_ShowChar(2,10,'.');
    OLED_ShowNum(2,7,T,3);
    OLED_ShowNum(2,11,(uint32_t)(T*10000)%10000,2);
}

void OLED_DHT11_Temp()
{
	
    DHT11_Read_Data(&TempH,&TempL,&HumiH,&HumiL);	
	
	printf("Tem:%d ¡æ\r\n", TempH);
	printf("Tem:%d ¡æ\r\n", TempL);
    printf("Hum:%d %%H\r\n", HumiH);
    printf("Hum:%d %%H\r\n", HumiL);
    
	OLED_ShowString(3,1,"Temp:");
	OLED_ShowChar(3,13,'¡æ');
    OLED_ShowNum(3,6,TempH,2);
	//OLED_ShowChar(3,6,'0'+(TempH/10));
	//OLED_ShowChar(3,7,'0'+(TempH%10));

	OLED_ShowChar(3,9,'0'+(TempL/10));
	OLED_ShowChar(3,10,'0'+(TempL%10));	
	OLED_ShowChar(3,8,':');	
	OLED_ShowChar(3,8,'.');
	
    OLED_ShowString(4,1,"Humi:");
    OLED_ShowString(4,13,"%RH");
	OLED_ShowChar(4,6,'0'+(HumiH/10));
	OLED_ShowChar(4,7,'0'+(HumiH%10));
	OLED_ShowChar(4,9,'0'+(HumiL/10));
	OLED_ShowChar(4,10,'0'+(HumiL%10));
	OLED_ShowChar(4,8,':');	
	OLED_ShowChar(4,8,'.');
}
