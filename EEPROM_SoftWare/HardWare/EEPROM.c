#include "EEPROM.h"

/****
	* @brief	EEPROM初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage:IIC_Init();
    */
void EEPROM_Init()
{
    IIC_Init();
}

/****
	* @brief	EEPROM写入一字节数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
    * @param   	Byte    要写入的数据
	* @return   无  	
	* Sample usage:EEPROM_Byte_Write(1,0x04);
    */
void EEPROM_Byte_Write(uint8_t Addr,uint8_t Byte)
{
    IIC_Start();
    IIC_SendByte(EEPROM_ADDR);
    IIC_ReceiveAck();
    IIC_SendByte(Addr);
    IIC_ReceiveAck();
    IIC_SendByte(Byte);
    IIC_ReceiveAck();
    IIC_Stop();
	Delay_ms(2);
}

#if 0
/****
	* @brief	EEPROM写入一页数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
    * @param   	Byte    要写入的数据的地址
    * @param   	Num     要写入的个数  0-8
	* @return   无  	
	* Sample usage:EEPROM_Page_Write(1,arr,8);
    */
void EEPROM_Page_Write(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    IIC_Start();
    IIC_SendByte(EEPROM_ADDR);
    IIC_ReceiveAck();
    IIC_SendByte(Addr);
    IIC_ReceiveAck();
    while(Num--)
    {
        IIC_SendByte(*Byte++);
        IIC_ReceiveAck();
    }
    IIC_Stop();
    Delay_ms(2);
}
#else
/****
	* @brief	EEPROM写入一页数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
    * @param   	Byte    要写入的数据的地址
    * @param   	Num     要写入的个数  0-8
	* @return   无  	
	* Sample usage:EEPROM_Page_Write(1,arr,8);
    */
void EEPROM_Page_Write(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    while(Num--)
    {
        EEPROM_Byte_Write(Addr++,*Byte++);
        Delay_ms(2);
    }
}
#endif

/****
	* @brief	EEPROM读取数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
	* @return   Byte  	读取的数据
	* Sample usage:EEPROM_Random_Read(1);
    */
uint8_t EEPROM_Random_Read(uint8_t Addr)
{
    uint8_t Byte = 0;
    IIC_Start();
    IIC_SendByte(EEPROM_ADDR);
    IIC_ReceiveAck();
    IIC_SendByte(Addr);
    IIC_ReceiveAck();

    IIC_Start();
    IIC_SendByte(EEPROM_ADDR | 0x01);
    IIC_ReceiveAck();
    Byte = IIC_ReceiveByte();
    IIC_Stop();
    return Byte;
}

/****
	* @brief	EEPROM连续读取数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
	* @return   Byte  	读取的数据
    * @param   	Num     要写入的个数  
	* Sample usage:EEPROM_Sequential_Read(1,arr,8);
    */
void EEPROM_Sequential_Read(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    while(Num--)
    {
        *Byte++ = EEPROM_Random_Read(Addr++);
    }
}


