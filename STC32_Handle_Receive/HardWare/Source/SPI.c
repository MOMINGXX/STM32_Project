#include "SPI.h"

/****
	* @brief	SPI引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:SPI_GPIO_Config()();
    */
static void SPI_GPIO_Config()
{
	P1M1 &= ~0x38;
    P1M0 &= ~0x38;      //P13 P14 P15为准双向口  0011 1000

    P5M0 = 0x00; 
	P5M1 = 0x00; 		//P50为准双向口
	
	SPI_CS = 1;
	SPI_SCK = 0;
}

/****
	* @brief	SPI配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:SPI_Config();
    */
static void SPI_Config()
{
	SPDAT = 0x00;			//初始化SPI数据
	SPSTAT = 0xC0;			//清除SPI状态位  
    SPCTL = 0xD3;          //忽略SS-使能SPI-高位先行-主机模式-时钟空闲时为低、上升沿(第1个边沿)采样
}

/****
	* @brief	SPI初始化  
	* @param   	无
	* @return   无 	
	* Sample usage:SPI_Init();
    */
void SPI_Init()
{
    SPI_GPIO_Config();
    #if HARD
    SPI_Config();
    #endif
}

/****
	* @brief	SPI 发送 接收 一个字节数据   		  
	* @param	Byte	发送的数据
	* @return   ByteReceive 接收的数据 	
	* Sample usage:SOFT_SPI_Config();
    */
#if SOFT	//软件模拟SPI
uint8_t SPI_Send_ReceiveByte(uint8_t Byte)
{
	uint8_t i, ByteReceive = 0x00;
	
	for (i = 0; i < 8; i ++)
	{
		SPI_MOSI = (Byte & (0x80 >> i));
		SPI_SCK = 1;
		if (SPI_MISO == 1){ByteReceive |= (0x80 >> i);}
		SPI_SCK = 0;
	}
	return ByteReceive;
}

#elif HARD		//硬件SPI
uint8_t SPI_Send_ReceiveByte(uint8_t Byte)
{
    SPDAT = Byte;
    while(!(SPSTAT & 0x80));		//等待传输完成SPIF=0
    SPSTAT &= ~0x3F;				//传输完成后置SPIF=1、WCOL=1清除标志
	return SPDAT;
}
#endif

/****
	* @brief	SPI 发送一个字节数据   		  
	* @param	ByteSend	发送的数据
    * @return   无
	* Sample usage:SPI_SendByte(1);
    */
void SPI_SendByte(uint8_t Byte)
{
    SPDAT = Byte;
    while(!(SPSTAT & 0x80)); 		//等待传输完成SPIF=0
    SPSTAT &= ~0x3F;         		//传输完成后置SPIF=1、WCOL=1清除标志
}

/****
	* @brief	SPI 发送 接收 一个字节数据   		  
	* @param	无
	* @return   SPDAT 接收的数据 	
	* Sample usage:SPI_ReceiveByte();
    */
uint8_t SPI_ReceiveByte()
{
    SPDAT = 0xff;
    while(!(SPSTAT & 0x80));		//等待传输完成SPIF=0
    SPSTAT &= ~0x3F;        		//传输完成后置SPIF=1、WCOL=1清除标志
    return SPDAT;
}

