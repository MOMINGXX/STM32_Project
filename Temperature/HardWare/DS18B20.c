#include "DS18B20.h"

/****
	* @brief	读取引脚状态    			  
	* @param   	无
	* @return   BitValue    读取的状态 0 / 1 	
	* Sample usage:DS18B20_R_WireBus();
    */
static uint8_t DS18B20_R_WireBus()
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);
    return BitValue;
}

/****
	* @brief	输入输出模式选择 			  
	* @param   	Mode	选择的模式 	DS18B20_OUTPUT  DS18B20_INPUT
	* @return   无  	
	* Sample usage:DS18B20_Mode_Select(DS18B20_OUTPUT);
    */
void DS18B20_Mode_Select(DS18B20_InitTypedef Mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(Mode)	//Mode == DS18B20_OUTPUT
	{
		GPIO_InitStruct.GPIO_Pin = DS18B20_GPIO_PIN ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	}
	else		//Mode == DS18B20_INPUT
	{
		GPIO_InitStruct.GPIO_Pin = DS18B20_GPIO_PIN ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	}
	GPIO_Init(DS18B20_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	DS18B20 初始化    			  
	* @param   	无
	* @return   无  	
	* Sample usage:DS18B20_Init();
    */
void DS18B20_Init()
{
	DS18B20_Mode_Select(DS18B20_OUTPUT);
    DS18B20_WIREBUS(1);
    DS18B20_WIREBUS(0);
    Delay_us(500);
    DS18B20_WIREBUS(1);
    Delay_us(550);
}

/****
	* @brief	DS18B20 写一位数据    			  
	* @param   	Bit		要写的一位数据   	
	* @return   无  	
	* Sample usage:DS18B20_WriteBit(0x01);
    */
void DS18B20_WriteBit(uint8_t Bit)
{
	DS18B20_Mode_Select(DS18B20_OUTPUT);
	DS18B20_WIREBUS(0);
	Delay_us(10);
	DS18B20_WIREBUS(Bit);
	Delay_us(50);
    DS18B20_WIREBUS(1);
}

/****
	* @brief	DS18B20 写一个字节数据    			  
	* @param   	Bit		要写的字节数据   	
	* @return   无  	
	* Sample usage:DS18B20_WriteByte( Byte);
    */
void DS18B20_WriteByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		DS18B20_WriteBit(Byte & (0x01 << i));
	}
}

/****
	* @brief	DS18B20 读一位数据    			  
	* @param   	无		   	
	* @return   Bit  	读到的数据
	* Sample usage:DS18B20_ReadBit();
    */
uint8_t DS18B20_ReadBit()
{
	uint8_t Bit;
	DS18B20_Mode_Select(DS18B20_OUTPUT);
	DS18B20_WIREBUS(0);
	Delay_us(5);
	DS18B20_WIREBUS(1);
	DS18B20_Mode_Select(DS18B20_INPUT);
	Delay_us(5);
	Bit = DS18B20_R_WireBus();
	Delay_us(50);
	return Bit;	
}

/****
	* @brief	DS18B20 读一字节数据    			  
	* @param   	无		   	
	* @return   Byte  	读到的字节数据
	* Sample usage:DS18B20_ReadBit();
    */
uint8_t DS18B20_ReadByte()
{
	uint8_t i;
	uint8_t Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(DS18B20_ReadBit())
		{
			Byte |= (0x01 << i);
		}
	}
	return Byte;
}

/****
	* @brief	DS18B20 温度转换  			  
	* @param   	无		   	
	* @return   无
	* Sample usage:DS18B20_ConvertT();
    */
void DS18B20_ConvertT()
{
	DS18B20_Init();
	DS18B20_WriteByte(DS18B20_SKIP_ROM);
	DS18B20_WriteByte(DS18B20_CONVERT_T);
}

/****
	* @brief	DS18B20 读取温度数据			  
	* @param   	无		   	
	* @return   T	读到的温度数据
	* Sample usage:DS18B20_ReadT();
    */
float DS18B20_ReadT()
{
	uint8_t TLSB,TMSB;
	int Temp;
	float T;
	DS18B20_Init();
	DS18B20_WriteByte(DS18B20_SKIP_ROM);
	DS18B20_WriteByte(DS18B20_READ_SCRATCHPAD);
	TLSB=DS18B20_ReadByte();
	TMSB=DS18B20_ReadByte();
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;
	return T;
}

