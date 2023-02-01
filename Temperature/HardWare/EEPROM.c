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
	Delay_ms(5);
}

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
    Delay_ms(5);
}

/****
	* @brief	EEPROM写入数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
    * @param   	Byte    要写入的数据的地址
    * @param   	Num     要写入的个数  0-255
	* @return   无  	
	* Sample usage:EEPROM_Buffer_Write(1,arr,8);
    */
void EEPROM_Buffer_Write(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr_Temp = 0, count = 0;

    Addr_Temp = Addr % EEPROM_PageSize;
    count = EEPROM_PageSize - Addr_Temp;
    NumOfPage =  Num / EEPROM_PageSize;
    NumOfSingle = Num % EEPROM_PageSize;
    
    /* If Addr is EEPROM_PageSize aligned  */
    if(Addr_Temp == 0) 
    {
        /* If Num < EEPROM_PageSize */
        if(NumOfPage == 0) 
        {
            EEPROM_Page_Write(Addr, Byte, NumOfSingle);
        }
        /* If Num > EEPROM_PageSize */
        else  
        {
            while(NumOfPage--)
            {
                EEPROM_Page_Write(Addr, Byte, EEPROM_PageSize); 
                Addr +=  EEPROM_PageSize;
                Byte += EEPROM_PageSize;
            }

            if(NumOfSingle!=0)
            {
                EEPROM_Page_Write(Addr, Byte, NumOfSingle);
            }
        }
    }
    /* If Addr is not EEPROM_PageSize aligned  */
    else 
    {
        /* If Num < EEPROM_PageSize */
        if(NumOfPage== 0) 
        {
            EEPROM_Page_Write(Addr, Byte, NumOfSingle);
        }
        /* If Num > EEPROM_PageSize */
        else
        {
            Num -= count;
            NumOfPage =  Num / EEPROM_PageSize;
            NumOfSingle = Num % EEPROM_PageSize;	
            
            if(count != 0)
            {  
                EEPROM_Page_Write(Addr, Byte, count);
                Addr += count;
                Byte += count;
            } 
            
            while(NumOfPage--)
            {
                EEPROM_Page_Write(Addr, Byte, EEPROM_PageSize);
                Addr +=  EEPROM_PageSize;
                Byte += EEPROM_PageSize;  
            }
            if(NumOfSingle != 0)
            {
                EEPROM_Page_Write(Addr, Byte, NumOfSingle); 
            }
        }
    }  
}

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
    IIC_SendAck(1);
    IIC_Stop();
    return Byte;
}

/****
	* @brief	EEPROM连续读取数据    			  
	* @param   	Addr    EEPROM内部存储单元地址
	* @return   Byte  	读取的数据
    * @param   	Num     要写入的个数  0-255
	* Sample usage:EEPROM_Sequential_Read(1,arr,8);
    */
void EEPROM_Sequential_Read(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    IIC_Start();
    IIC_SendByte(EEPROM_ADDR);
    IIC_ReceiveAck();
    IIC_SendByte(Addr);
    IIC_ReceiveAck();

    IIC_Start();
    IIC_SendByte(EEPROM_ADDR | 0x01);
    IIC_ReceiveAck();
    for (int i = 0; i < Num + 1; i++)
    {
        *Byte++ = IIC_ReceiveByte();
        if(Num == i) 
        {
            IIC_SendAck(1);
        }
        else
        {
            IIC_Ack();
        }
    }
    IIC_Stop();
}


