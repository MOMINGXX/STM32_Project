#include "Deal.h"

uint8_t TempH,TempL,HumiH,HumiL;
int8_t Alert_Temp[2];
uint8_t Mode = 0;
uint8_t KeyNumber_Temp = 0;
float T;

/****
	* @brief	数据处理 初始化 			  
	* @param   	无
	* @return   无 	
	* Sample usage:Deal_Init();
    */
void Deal_Init()
{
    Usart_Init();
	TIMx_Init();
	DS18B20_CLK_ENABLE;
	DHT11_CLK_ENABLE;
    EEPROM_Init();
	DS18B20_ConvertT();
	OLED_Init();

	Alert_Temp[0] = EEPROM_Random_Read(0);
	Alert_Temp[1] = EEPROM_Random_Read(1);
	if(Alert_Temp[0] > 125 || Alert_Temp[1] < -55 || Alert_Temp[0] <= Alert_Temp[1])
	{
		Alert_Temp[0] = 30;
		Alert_Temp[1] = -10;
	}
}

/****
	* @brief	按键扫描			  
	* @param   	无
	* @return   无 	
	* Sample usage:ey_Get();
    */
void Key_Get()
{
	KeyNumber_Temp = KEY_GetNumber();
}

/****
	* @brief	显示DS18B20 测得温度 			  
	* @param   	x	OLED 显示行位置  x = 1(黄色) 2 3 4
	* @return   无 	
	* Sample usage:OLED_DS18B20_Temp(2);
    */
void OLED_DS18B20_Temp(uint8_t x)
{
	if(x <= 4 && x >= 1)
	{
		OLED_ShowString(x,1,"Temp:");
		//OLED_ShowChar(x,13,'℃');
		DS18B20_ConvertT();
		T=DS18B20_ReadT();
		printf("\r\nwd:>%f\n",T);
		if(T<0)
		{
			OLED_ShowNum(x,7,T,3);
			OLED_ShowNum(x,11,(uint32_t)(T*10000)%10000,2);
			OLED_ShowChar(x,10,'.');
			OLED_ShowChar(x,6,'-');
		}
		OLED_ShowChar(x,10,'.');
		OLED_ShowNum(x,7,T,3);
		OLED_ShowNum(x,11,(uint32_t)(T*10000)%10000,2);
	}
	else
	{
		OLED_ShowString(1,1,"Wrong Position!");
	}
}

/****
	* @brief	显示DHT11 测得温度 			  
	* @param   	无
	* @return   无 	
	* Sample usage:OLED_DHT11_Temp();
    */
void OLED_DHT11_Temp()
{
	
    DHT11_Read_Data(&TempH,&TempL,&HumiH,&HumiL);	
	
	//printf("Tem:%d ℃\r\n", TempH);
	//printf("Tem:%d ℃\r\n", TempL);
    printf("Hum:%d %%H\r\n", HumiH);
    printf("Hum:%d %%H\r\n", HumiL);
    
	OLED_ShowString(3,1,"Temp:");
	OLED_ShowChar(3,13,95);
	OLED_ShowChar(3,14,'C');
    OLED_ShowNum(3,7,TempH,3);

	OLED_ShowNum(3,11,TempL,2);
	OLED_ShowChar(3,10,'.');
	
    OLED_ShowString(4,1,"Humi:");
    OLED_ShowString(4,13,"%RH");
	OLED_ShowNum(4,7,HumiH,3);
	OLED_ShowNum(4,11,HumiL,2);
	OLED_ShowChar(4,10,'.');
}

/****
	* @brief	显示DHT11 测得温度 			  
	* @param   	无
	* @return   无 	
	* Sample usage:OLED_DS18B20_Temp(2);
    */
void OLED_Alert_Temp()
{
	OLED_ShowString(2,1,"TempH:");
    OLED_ShowString(3,1,"TempL:");
	OLED_ShowNum(2,8,Alert_Temp[0],3);
	OLED_ShowChar(2,7,'+');
	OLED_ShowSignedNum(3,7,Alert_Temp[1],3);
	OLED_ShowChar(2,13,95);
	OLED_ShowChar(2,14,'C');
}

/****
	* @brief	预警温度设置			  
	* @param   	无
	* @return   无 	
	* Sample usage:Alert_Temp_Set();
    */
void Alert_Temp_Set()
{
	if(KeyNumber_Temp)
	{
		if(3 == KeyNumber_Temp)							//高温预警值 ++
		{
			Alert_Temp[0]++;
			if(Alert_Temp[0] > 125)
			{
				Alert_Temp[0] = 125;
			}
		}
		else if(4 == KeyNumber_Temp)					//高温预警值 --
		{
			Alert_Temp[0]--;
			if(Alert_Temp[0] <= Alert_Temp[1])
			{
				Alert_Temp[0]++;
			} 
		}
		else if(5 == KeyNumber_Temp)					//低温预警值 ++
		{
			Alert_Temp[1]++;
			if(Alert_Temp[1] >= Alert_Temp[0])
			{
				Alert_Temp[1]--;
			} 
		}
		else if(6 == KeyNumber_Temp)					//低温预警值 --
		{
			Alert_Temp[1]--;
			if(Alert_Temp[1] < -55)
			{
				Alert_Temp[1] = -55;
			}
		}
		EEPROM_Byte_Write(0,Alert_Temp[0]);
		EEPROM_Byte_Write(1,Alert_Temp[1]);
		OLED_Alert_Temp();
	}
}	

/****
	* @brief	模式的选择					  
	* @param   	无
	* @return   无 	
	* Sample usage:Deal_Mode_Select();
    */
void Deal_Mode_Select()
{
	if(1 == KeyNumber_Temp)
	{
		OLED_Clear();
		//Mode = 1;
		if(Mode)
		{
			Mode = 0;
		}
		else
		{
			Mode = 1;
		}
	}
	if(2 == KeyNumber_Temp)
	{
		OLED_Clear();
		Mode = 2;
	}
	switch(Mode)
	{
		case 0:	
			OLED_ShowString(1,1,"Temp Humi Test!");
			OLED_DS18B20_Temp(2);
			OLED_DHT11_Temp();
			break;
		case 1:	
			OLED_ShowString(1,1,"Temp Warning !");
			OLED_Alert_Temp();	
			break;
		case 2:	
			OLED_ShowString(1,1,"Temp Alert Set!");
			Alert_Temp_Set();	
			break;
		default:
			OLED_ShowString(1,1,"Select ERROR !");
			break;
	}
}

/****
	* @brief	温度报警		  
	* @param   	无
	* @return   无 	
	* Sample usage:Temp_Alarm();
    */
void Temp_Alarm()
{
	Deal_Mode_Select();
	if(T > Alert_Temp[0])
	{
		OLED_Clear();
		OLED_DS18B20_Temp(1);
		OLED_ShowString(2,1,"Warning...!!!");
		OLED_ShowString(3,1,"High Temp !!!");
		Delay_ms(1000);
	}		
	else if(T < Alert_Temp[1])
	{
		OLED_Clear();
		OLED_DS18B20_Temp(1);
		OLED_ShowString(2,1,"Warning...!!!");
		OLED_ShowString(3,1,"Low Temp  !!!");
		Delay_ms(1000);
	}	

}