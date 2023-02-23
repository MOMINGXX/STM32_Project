#include "NRF24L01.h"

/****
	* @brief    NRF24L01 引脚 配置	  
	* @param   	无
	* @return   无	
	* Sample usage:NRF24L01_GPIO_Config();
    */
void NRF24L01_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //开启GPIO时钟
    NRF24L01_GPIO_APBxClockCMD(NRF24L01_GPIO_CLK,ENABLE);
    //参数配置 CE , CSN , IRQ
    GPIO_InitStruct.GPIO_Pin = NRF24L01_IRQ_GPIO_PIN | NRF24L01_CSN_GPIO_PIN | NRF24L01_CE_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //参数配置 CSK
    GPIO_InitStruct.GPIO_Pin = NRF24L01_SCK_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //参数配置 MISO
    GPIO_InitStruct.GPIO_Pin = NRF24L01_MISO_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //参数配置 MOSI
    GPIO_InitStruct.GPIO_Pin = NRF24L01_MOSI_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	Chip Enable, RX和TX模式选择   			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:NRF24L01_CE(1);
    */
static void NRF24L01_CE(uint8_t BitValue)
{
    GPIO_WriteBit(NRF24L01_GPIO_PORT,NRF24L01_CE_GPIO_PIN,(BitAction)BitValue);
}

/****
	* @brief	SPI chip select, 低电平使能   			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:NRF24L01_CSN(1);
    */
static void NRF24L01_CSN(uint8_t BitValue)
{
    GPIO_WriteBit(NRF24L01_GPIO_PORT,NRF24L01_CSN_GPIO_PIN,(BitAction)BitValue);
}

/****
	* @brief    NRF24L01 SPI 配置		  
	* @param   	无
	* @return   无	
	* Sample usage:NRF24L01_SPIx_Config();
    */
void NRF24L01_SPIx_Config()
{
    SPI_InitTypeDef SPI_InitStruct;
    //开启SPI时钟
    NRF24L01_SPIx_APBxClockCMD(NRF24L01_SPIx_CLK,ENABLE);
    //参数配置
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;   //波特率预分频值为 256 
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;       //数据捕获于第二个时钟沿
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;        //时钟悬空高
    SPI_InitStruct.SPI_CRCPolynomial = 7;           //CRC 校验
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;  //SPI 发送接收 8 位帧结构
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;     //SPI 设置为双线双向全双工
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 位开始
    SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;       //设置为从 SPI
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;          //内部 NSS 信号有 SSI 位控制
    SPI_Init(NRF24L01_SPIx,&SPI_InitStruct);

    SPI_Cmd(NRF24L01_SPIx,ENABLE);

    NRF24L01_CSN(1);
}

/****
	* @brief    NRF24L01 初始化		  
	* @param   	无
	* @return   无	
	* Sample usage:NRF24L01_Init();
    */
void NRF24L01_Init()
{
    NRF24L01_GPIO_Config();
    NRF24L01_SPIx_Config();
}

/****
	* @brief    NRF24L01 收发一个字节	  
	* @param   	无
	* @return   无	
	* Sample usage:NRF24L01_Send_RecieveByte(DUMMY);
    */
uint8_t NRF24L01_Send_RecieveByte(uint8_t Byte)
{
    //检查并等待发送缓冲区为空
    while(RESET == SPI_I2S_GetFlagStatus(NRF24L01_SPIx,SPI_I2S_FLAG_TXE));
     //写入数据到缓冲区
    SPI_I2S_SendData(NRF24L01_SPIx,Byte);
    //检查并等待接收缓冲区为空
    while(RESET == SPI_I2S_GetFlagStatus(NRF24L01_SPIx,SPI_I2S_FLAG_RXNE));
    //接收数据
    return SPI_I2S_ReceiveData(NRF24L01_SPIx);
}




