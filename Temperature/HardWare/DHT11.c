#include "DHT11.h"

/****
	* @brief	读取引脚状态    			  
	* @param   	无
	* @return   BitValue    读取的状态 0 / 1 	
	* Sample usage:DHT11_R_WireBus();
    */
static uint8_t DHT11_R_WireBus()
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
    return BitValue;
}

/****
	* @brief	输入输出模式选择			  
	* @param   	Mode	选择的模式 	DHT11_OUTPUT  DHT11_INPUT
	* @return   无  	
	* Sample usage:DHT11_Mode_Select(DHT11_OUTPUT);
    */
static void DHT11_Mode_Select(DHT11_InitTypedef Mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(Mode)	//Mode == DHT11_OUTPUT
	{
		GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	}
	else		//Mode == DHT11_INPUT
	{
		GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	}
	GPIO_Init(DHT11_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	DHT11 重置     			  
	* @param   	无
	* @return   无 	
	* Sample usage: DHT11_Reset();
    */
static void DHT11_Reset()
{
    DHT11_Mode_Select(DHT11_OUTPUT);
    DHT11_WIREBUS(1);
    Delay_us(30);
    DHT11_WIREBUS(0);
    Delay_ms(20);
    DHT11_WIREBUS(1);
    Delay_us(30);
}

/****
	* @brief	等待DHT11 回应 			  
	* @param   	无		
	* @return  	true	检测到DHT11(实际为 0)
	*     @arg	false	未检测到DHT11(实际为 1)
	* Sample usage:DHT11_Check();
    */
bool DHT11_Check()
{
	uint8_t retry = 0;
	DHT11_Mode_Select(DHT11_INPUT);
	while(DHT11_R_WireBus() && retry <100)
	{
		retry++;
		Delay_us(1);
	}
	if(retry >= 100)
	{
		return false;
	}
	else
	{
		retry = 0;
	}
	while(!DHT11_R_WireBus() && retry <100)
	{
		retry++;
		Delay_us(1);
	}
	if(retry >= 100)
	{
		return false;
	}
	return true;
}


/****
	* @brief	DHT11 读取引脚状态    			  
	* @param   	无
	* @return   0 / 1  	
	* Sample usage:DHT11_Init();
    */
uint8_t DHT11_Read_Bit()
{
	DHT11_Mode_Select(DHT11_INPUT);
    while(DHT11_R_WireBus());           //等待低电平 开始传输数据
    while(!DHT11_R_WireBus());          //等待高电平
    Delay_us(60);
    if(DHT11_R_WireBus())
    {
        return 1;
    }
    return 0;
}                                     

/****
	* @brief	DHT11 读取数据   			  
	* @param   	无
	* @return   Byte    读取的数据  	
	* Sample usage:DHT11_Read_Byte();
    */
uint8_t DHT11_Read_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    for(i = 0; i < 8; i++)
    {
        Byte <<= 1;
        Byte |= DHT11_Read_Bit();
    }
	return Byte;
}
/*
uint8_t DHT11_Read_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
	DHT11_Mode_Select(DHT11_INPUT);
    for(i = 0; i < 8; i++)
    {
		
        while(DHT11_R_WireBus());       //等待低电平 开始传输数据
        while(!DHT11_R_WireBus());
        Delay_us(60);
        Byte <<= 1;
        if(DHT11_R_WireBus() == 1)
        {
            Byte += 1;
        }
        while(DHT11_R_WireBus());       //等待低电平 开始传输下一个数据
    }
    return Byte;
}
*/

/****
	* @brief	DHT11 读取温湿度数据   			  
	* @param   	Data    存储读取的温湿度数据 
	* @return   0 / 1   0>读取的数据错误         1    	
	* Sample usage:DHT11_Read_Data(&TempH,&TempL,&HumiH,&HumiL);
    */
void DHT11_Read_Data(uint8_t *TempH,uint8_t *TempL,uint8_t *HumiH,uint8_t *HumiL)
{
	uint8_t i;
    uint8_t Buff[5];
	DHT11_Reset();
	if(DHT11_Check())
	{
		for(i=0;i<5;i++)
		{
			Buff[i] = DHT11_Read_Byte();
		}
		if(Buff[4] == Buff[0] + Buff[1] + Buff[2] + Buff[3])
		{
			*HumiH = Buff[0];
			*HumiL = Buff[1];
			*TempH = Buff[2];
			*TempL = Buff[3];
		}
	}
}

