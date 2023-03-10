#include "I2C.h"

/****
	* @brief	I2C_SCL 引脚写入0 / 1     			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:IIC_SCL(1);
    */
static void I2C_SCL(uint8_t BitValue)
{
    I2C_SCL_PIN = BitValue;
    //Delay10us();
}

/****
	* @brief	I2C_SDA 引脚写入0 / 1     			  
	* @param   	BitValue    写入的 0 / 1 
	* @return   无  	
	* Sample usage:IIC_SDA(1);
    */
static void I2C_SDA(uint8_t BitValue)
{
    I2C_SDA_PIN = BitValue;
    //Delay10us();
}

/****
	* @brief	I2C_SDA 读取引脚状态    			  
	* @param   	无
	* @return   BitValue    读取的状态 0 / 1 	
	* Sample usage:IIC_R_SDA();
    */
static uint8_t I2C_R_SDA()
{
    uint8_t BitValue;
    BitValue = I2C_SDA_PIN;
    //Delay10us();
    return BitValue;
}

/****
	* @brief	开启 I2C   			  
	* @param   	无		   	
	* @return   无
	* Sample usage:I2C_Start()
    */
void I2C_Start()
{
    I2C_SDA(1);
    I2C_SCL(1);
    I2C_SDA(0);
    I2C_SCL(0);
}

/****
	* @brief	停止 I2C   			  
	* @param   	无		   	
	* @return   无
	* Sample usage:I2C_Start()
    */
void I2C_Stop()
{
    I2C_SDA(0);
    I2C_SCL(1);
    I2C_SDA(1);
}

/****
	* @brief	I2C 发送数据    			  
	* @param   	Byte    发送的数据 
	* @return   无  	
	* Sample usage:I2C_Write_Byte(0x01);
    */
void I2C_Write_Byte(uint8_t Byte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        I2C_SDA(Byte & (0x80 >> i));
        I2C_SCL(1);
        I2C_SCL(0);
    }
}

/****
	* @brief	I2C 接收数据    			  
	* @param   	无
	* @return   Byte    接收的数据  	
	* Sample usage:I2C_Receive_Byte();
    */
uint8_t I2C_Receive_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    I2C_SDA(1);
    for(i = 0; i < 8; i++)
    {
        I2C_SCL(1);
		if(I2C_R_SDA()){Byte|=(0x80>>i);}
		I2C_SCL(0);
    }
    return Byte;
}

/****
	* @brief	I2C 发送应答   			  
	* @param   	Ack     发送的应答   0 / 1
	* @return   无 	
	* Sample usage:I2C_SendAck(1);
    */
void I2C_Send_Ack(uint8_t Ack)
{
    I2C_SDA(Ack);
    I2C_SCL(1);
    I2C_SCL(0);
}

/****
	* @brief	I2C 接收应答   			  
	* @param   	无
	* @return   Ack 	接收的应答  0 / 1
	* Sample usage:I2C_Receive_Ack();
    */
uint8_t I2C_Receive_Ack()
{
    uint8_t Ack = 0;
    I2C_SDA(1);
    I2C_SCL(1);
    Ack = I2C_R_SDA();
    I2C_SCL(0);
    return Ack;
}
