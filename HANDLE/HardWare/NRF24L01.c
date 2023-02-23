#include "NRF24L01.h"

/****
	* @brief    NRF24L01 ���� ����	  
	* @param   	��
	* @return   ��	
	* Sample usage:NRF24L01_GPIO_Config();
    */
void NRF24L01_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //����GPIOʱ��
    NRF24L01_GPIO_APBxClockCMD(NRF24L01_GPIO_CLK,ENABLE);
    //�������� CE , CSN , IRQ
    GPIO_InitStruct.GPIO_Pin = NRF24L01_IRQ_GPIO_PIN | NRF24L01_CSN_GPIO_PIN | NRF24L01_CE_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //�������� CSK
    GPIO_InitStruct.GPIO_Pin = NRF24L01_SCK_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //�������� MISO
    GPIO_InitStruct.GPIO_Pin = NRF24L01_MISO_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);

    //�������� MOSI
    GPIO_InitStruct.GPIO_Pin = NRF24L01_MOSI_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(NRF24L01_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	Chip Enable, RX��TXģʽѡ��   			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:NRF24L01_CE(1);
    */
static void NRF24L01_CE(uint8_t BitValue)
{
    GPIO_WriteBit(NRF24L01_GPIO_PORT,NRF24L01_CE_GPIO_PIN,(BitAction)BitValue);
}

/****
	* @brief	SPI chip select, �͵�ƽʹ��   			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:NRF24L01_CSN(1);
    */
static void NRF24L01_CSN(uint8_t BitValue)
{
    GPIO_WriteBit(NRF24L01_GPIO_PORT,NRF24L01_CSN_GPIO_PIN,(BitAction)BitValue);
}

/****
	* @brief    NRF24L01 SPI ����		  
	* @param   	��
	* @return   ��	
	* Sample usage:NRF24L01_SPIx_Config();
    */
void NRF24L01_SPIx_Config()
{
    SPI_InitTypeDef SPI_InitStruct;
    //����SPIʱ��
    NRF24L01_SPIx_APBxClockCMD(NRF24L01_SPIx_CLK,ENABLE);
    //��������
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;   //������Ԥ��ƵֵΪ 256 
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;       //���ݲ����ڵڶ���ʱ����
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;        //ʱ�����ո�
    SPI_InitStruct.SPI_CRCPolynomial = 7;           //CRC У��
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;  //SPI ���ͽ��� 8 λ֡�ṹ
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;     //SPI ����Ϊ˫��˫��ȫ˫��
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //���ݴ���� MSB λ��ʼ
    SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;       //����Ϊ�� SPI
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;          //�ڲ� NSS �ź��� SSI λ����
    SPI_Init(NRF24L01_SPIx,&SPI_InitStruct);

    SPI_Cmd(NRF24L01_SPIx,ENABLE);

    NRF24L01_CSN(1);
}

/****
	* @brief    NRF24L01 ��ʼ��		  
	* @param   	��
	* @return   ��	
	* Sample usage:NRF24L01_Init();
    */
void NRF24L01_Init()
{
    NRF24L01_GPIO_Config();
    NRF24L01_SPIx_Config();
}

/****
	* @brief    NRF24L01 �շ�һ���ֽ�	  
	* @param   	��
	* @return   ��	
	* Sample usage:NRF24L01_Send_RecieveByte(DUMMY);
    */
uint8_t NRF24L01_Send_RecieveByte(uint8_t Byte)
{
    //��鲢�ȴ����ͻ�����Ϊ��
    while(RESET == SPI_I2S_GetFlagStatus(NRF24L01_SPIx,SPI_I2S_FLAG_TXE));
     //д�����ݵ�������
    SPI_I2S_SendData(NRF24L01_SPIx,Byte);
    //��鲢�ȴ����ջ�����Ϊ��
    while(RESET == SPI_I2S_GetFlagStatus(NRF24L01_SPIx,SPI_I2S_FLAG_RXNE));
    //��������
    return SPI_I2S_ReceiveData(NRF24L01_SPIx);
}




