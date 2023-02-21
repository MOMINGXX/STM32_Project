#include "USER_I2C.h"

/****
	* @brief	IIC_SCL 引脚写入0 / 1     			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:IIC_SCL(1);
    */
static void IIC_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(IIC_GPIO_PORT,IIC_SCL_GPIO_PIN,(BitAction)BitValue);
    Delay_us(10);
}

/****
	* @brief	IIC_SDA 引脚写入0 / 1     			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:IIC_SDA(1);
    */
static void IIC_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(IIC_GPIO_PORT,IIC_SDA_GPIO_PIN,(BitAction)BitValue);
    Delay_us(10);
}

/****
	* @brief	IIC_SDA 读取引脚状态    			  
	* @param   	无
	* @return   BitValue    读取的状态 0 / 1 	
	* Sample usage:IIC_R_SDA();
    */
static uint8_t IIC_R_SDA()
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(IIC_GPIO_PORT,IIC_SDA_GPIO_PIN);
    Delay_us(10);
    return BitValue;
}

/****
	* @brief	I2C 引脚配置   			  
	* @param   	无
	* @return   无  	
	* Sample usage:IIC_Init();
    */
void IIC_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //开启GPIO时钟
    IIC_GPIO_APBxCLKCMD(IIC_GPIO_CLK,ENABLE);
    //参数配置
    GPIO_InitStruct.GPIO_Pin = IIC_SCL_GPIO_PIN | IIC_SDA_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL_GPIO_PIN | IIC_SDA_GPIO_PIN);
}

/****
	* @brief	IIC 初始化    			  
	* @param   	无
	* @return   无  	
	* Sample usage:IIC_Init();
    */
void IIC_Init()
{
    IIC_GPIO_Config();
}

/****
	* @brief	IIC START     			  
	* @param   	无
	* @return   无  	
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
	* @param   	无
	* @return   无  	
	* Sample usage:IIC_Stop();
    */
void IIC_Stop()
{
    IIC_SDA(0);
    IIC_SCL(1);
    IIC_SDA(1);
}

/****
	* @brief	IIC 发送数据    			  
	* @param   	Byte    发送的数据 
	* @return   无  	
	* Sample usage:IIC_SendByte(0x01);
    */
void IIC_SendByte(uint8_t Byte)
{
    uint8_t i = 0 ;
    for(i = 0; i < 8; i++)
    {
        IIC_SDA(Byte & (0x80 >> i));
        IIC_SCL(1);
        IIC_SCL(0);
    }
}

/****
	* @brief	IIC 接收数据    			  
	* @param   	无
	* @return   Byte    接收的数据  	
	* Sample usage:IIC_ReceiveByte();
    */
uint8_t IIC_ReceiveByte()
{
    uint8_t i = 0 ;
     uint8_t Byte = 0x00;
    for(i = 0; i < 8; i++)
    {
        IIC_SCL(1);
        if(IIC_R_SDA())
        {
            Byte |= (0x80 >> i);
        }
        IIC_SCL(0);
    }
    return Byte;
}

/****
	* @brief	IIC 发送应答   			  
	* @param   	Ack     发送的应答   0 / 1
	* @return   无 	
	* Sample usage:IIC_SendAck(1);
    */
void IIC_SendAck(uint8_t Ack)
{
    IIC_SDA(Ack);
    IIC_SCL(1);
    IIC_SCL(0);
    
}

/****
	* @brief	IIC 接收应答   			  
	* @param   	无
	* @return   Ack 	接收的应答  0 / 1
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

