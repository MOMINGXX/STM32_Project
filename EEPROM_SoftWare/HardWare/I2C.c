#include "I2C.h"

/****
	* @brief	IIC_SCL ����д��0 / 1     			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:IIC_SCL(1);
    */
static void IIC_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(IIC_SCL_GPIO_PORT,IIC_SCL_GPIO_PIN,(BitAction)BitValue);
    Delay_us(10);
}

/****
	* @brief	IIC_SDA ����д��0 / 1     			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:IIC_SDA(1);
    */
static void IIC_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(IIC_SDA_GPIO_PORT,IIC_SDA_GPIO_PIN,(BitAction)BitValue);
    Delay_us(10);
}

/****
	* @brief	IIC_SDA ��ȡ����״̬    			  
	* @param   	��
	* @return   BitValue    ��ȡ��״̬ 0 / 1 	
	* Sample usage:IIC_R_SDA();
    */
static uint8_t IIC_R_SDA()
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(IIC_SDA_GPIO_PORT,IIC_SDA_GPIO_PIN);
    Delay_us(10);
    return BitValue;
}

/****
	* @brief	EEPROM��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:IIC_Init();
    */
void IIC_Init()
{
    //GPIO �ṹ��
    GPIO_InitTypeDef GPIO_InitStruct;
    //����GPIOʱ��
    IIC_GPIO_APBxCLKCMD(IIC_SCL_GPIO_CLK | IIC_SDA_GPIO_CLK,ENABLE);
    //����GPIO ����
    GPIO_InitStruct.GPIO_Pin = IIC_SCL_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_SCL_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = IIC_SDA_GPIO_PIN;
    GPIO_Init(IIC_SDA_GPIO_PORT,&GPIO_InitStruct);

    IIC_SDA(1);
    IIC_SCL(1);
}

/****
	* @brief	IIC START     			  
	* @param   	��
	* @return   ��  	
	* Sample usage:IIC_Start();
    */
void IIC_Start()
{
    IIC_SDA(1);
    IIC_SCL(1);
    IIC_SDA(0);
    IIC_SCL(0);
}

/****
	* @brief	IIC STOP     			  
	* @param   	��
	* @return   ��  	
	* Sample usage:IIC_Stop();
    */
void IIC_Stop()
{
    IIC_SDA(0);
    IIC_SCL(1);
    IIC_SDA(1);
}

/****
	* @brief	IIC ��������    			  
	* @param   	Byte    ���͵����� 
	* @return   ��  	
	* Sample usage:IIC_SendByte(0x01);
    */
void IIC_SendByte(uint8_t Byte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i ++)
    {
        IIC_SDA(Byte & (0x80>>i));
        IIC_SCL(1);
        IIC_SCL(0);
    }
}

/****
	* @brief	IIC ��������    			  
	* @param   	��
	* @return   Byte    ���յ�����  	
	* Sample usage:IIC_ReceiveByte();
    */
uint8_t IIC_ReceiveByte()
{
    uint8_t Byte = 0x00;
    uint8_t i = 0;
    IIC_SDA(1);
    for(i = 0; i < 8; i ++)
    {
        IIC_SCL(1);
        if(1 == IIC_R_SDA())
        {
            Byte |= (0x80>>i);
        }
        IIC_SCL(0);
    }
    return Byte;
}

/****
	* @brief	IIC ����Ӧ��   			  
	* @param   	Ack     ���͵�Ӧ��   0 / 1
	* @return   �� 	
	* Sample usage:IIC_SendAck(1);
    */
void IIC_SendAck(uint8_t Ack)
{
    IIC_SDA(Ack);
    IIC_SCL(1);
    IIC_SCL(0);
    
}

/****
	* @brief	IIC ����Ӧ��   			  
	* @param   	��
	* @return   Ack 	���յ�Ӧ��  0 / 1
	* Sample usage:IIC_SendAck(1);
    */
uint8_t IIC_ReceiveAck()
{
    uint8_t Ack = 0x00;
    IIC_SDA(1);
    IIC_SCL(1);
    Ack = IIC_R_SDA();
    IIC_SCL(0);
    return Ack;
}



