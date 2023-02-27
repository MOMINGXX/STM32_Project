#include "SOFT_SPI.h"

/****
	* @brief	片选引脚输出高低电平	   		  
	* @param	BitValue   0/1	低/高电平
	* @return   无  	
	* Sample usage:SPI_W_CS(1);
    */
void SPI_W_CS(uint8_t BitValue)
{
	GPIO_WriteBit(SPI_GPIO_PORT,SPI_CS_GPIO_PIN, (BitAction)BitValue);
}

/****
	* @brief	SCK 输出高低电平	   		  
	* @param	BitValue   0/1	低/高电平
	* @return   无  	
	* Sample usage:SPI_W_SCK(1);
    */
static void SPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(SPI_GPIO_PORT, SPI_SCK_GPIO_PIN, (BitAction)BitValue);
}

/****
	* @brief	MISO 读引脚状态	   		  
	* @param	无
	* @return   BitValue   0/1	低/高电平  	
	* Sample usage:SPI_R_MISO(1);
    */
static uint8_t SPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(SPI_GPIO_PORT, SPI_MISO_GPIO_PIN);
}

/****
	* @brief	MOSI 输出高低电平	   		  
	* @param	BitValue   0/1	低/高电平
	* @return   无  	
	* Sample usage:SPI_W_MOSI(1);
    */
static void SPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(SPI_GPIO_PORT, SPI_MOSI_GPIO_PIN, (BitAction)BitValue);
}

/****
	* @brief	软件模拟SPI 引脚陪着	   		  
	* @param	无
	* @return   无  	
	* Sample usage:SOFT_SPI_Config();
    */
void SOFT_SPI_Config()
{
	RCC_APB2PeriphClockCmd(SPI_GPIO_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = SPI_CS_GPIO_PIN | SPI_SCK_GPIO_PIN | SPI_MOSI_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitStructure);
	
	SPI_W_CS(1);
	SPI_W_SCK(0);
}

/****
	* @brief	SPI 发送 接收 一个字节数据   		  
	* @param	ByteSend	发送的数据
	* @return   ByteReceive 接收的数据 	
	* Sample usage:SOFT_SPI_Config();
    */
uint8_t NRF24L01_Send_RecieveByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;
	
	for (i = 0; i < 8; i ++)
	{
		SPI_W_MOSI(ByteSend & (0x80 >> i));
		SPI_W_SCK(1);
		if (SPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}
		SPI_W_SCK(0);
	}
	return ByteReceive;
}

