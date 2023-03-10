#include "EEPROM.h"

/****
	* @brief	AT24C02写入一字节数据    			  
	* @param   	Write_Addr  AT24C02内部存储单元地址
    * @param   	Byte    	要写入的数据
	* @return   无  	
	* Sample usage:AT24C02_Byte_Write(1,0x04);
    */
void AT24C02_Byte_Write(uint8_t Write_Addr,uint8_t Byte)
{
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR);
	I2C_Receive_Ack();
	I2C_Write_Byte(Write_Addr);
	I2C_Receive_Ack();
	I2C_Write_Byte(Byte);
	I2C_Receive_Ack();
	I2C_Stop();
	//Delay(5);
}

/****
	* @brief	AT24C02写入一页数据    			  
	* @param   	Write_Addr    AT24C02内部存储单元地址
    * @param   	Byte    要写入的数据的地址
    * @param   	Num     要写入的个数  0-8
	* @return   无  	
	* Sample usage:AT24C02_Page_Write(1,arr,8);
    */
void AT24C02_Page_Write(uint8_t Write_Addr,uint8_t *Byte,uint8_t Num)
{
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR);
	I2C_Receive_Ack();
	I2C_Write_Byte(Write_Addr);
	I2C_Receive_Ack();
	while(Num--)
	{
		I2C_Write_Byte(*Byte++);
		I2C_Receive_Ack();
	}
	I2C_Stop();
	//Delay(5);
}

/****
	* @brief	AT24C02写入数据    			  
	* @param   	Addr    AT24C02内部存储单元地址
    * @param   	Byte    要写入的数据的地址
    * @param   	Num     要写入的个数  0-255
	* @return   无  	
	* Sample usage:AT24C02_Buffer_Write(1,arr,8);
    */
void AT24C02_Buffer_Write(uint8_t Write_Addr,uint8_t *Byte,uint8_t Num)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr_Temp = 0, count = 0;

    Addr_Temp = Write_Addr % AT24C02_PageSize;
    count = AT24C02_PageSize - Addr_Temp;
    NumOfPage =  Num / AT24C02_PageSize;
    NumOfSingle = Num % AT24C02_PageSize;
    
    /* If Write_Addr is AT24C02_PageSize aligned  */
    if(Addr_Temp == 0) 
    {
        /* If Num < AT24C02_PageSize */
        if(NumOfPage == 0) 
        {
            AT24C02_Page_Write(Write_Addr, Byte, NumOfSingle);
        }
        /* If Num > AT24C02_PageSize */
        else  
        {
            while(NumOfPage--)
            {
                AT24C02_Page_Write(Write_Addr, Byte, AT24C02_PageSize); 
                Write_Addr +=  AT24C02_PageSize;
                Byte += AT24C02_PageSize;
            }

            if(NumOfSingle!=0)
            {
                AT24C02_Page_Write(Write_Addr, Byte, NumOfSingle);
            }
        }
    }
    /* If Write_Addr is not AT24C02_PageSize aligned  */
    else 
    {
        /* If Num < AT24C02_PageSize */
        if(NumOfPage== 0) 
        {
            AT24C02_Page_Write(Write_Addr, Byte, NumOfSingle);
        }
        /* If Num > AT24C02_PageSize */
        else
        {
            Num -= count;
            NumOfPage =  Num / AT24C02_PageSize;
            NumOfSingle = Num % AT24C02_PageSize;	
            
            if(count != 0)
            {  
                AT24C02_Page_Write(Write_Addr, Byte, count);
                Write_Addr += count;
                Byte += count;
            } 
            
            while(NumOfPage--)
            {
                AT24C02_Page_Write(Write_Addr, Byte, AT24C02_PageSize);
                Write_Addr +=  AT24C02_PageSize;
                Byte += AT24C02_PageSize;  
            }
            if(NumOfSingle != 0)
            {
                AT24C02_Page_Write(Write_Addr, Byte, NumOfSingle); 
            }
        }
    }  
}

/****
	* @brief	AT24C02读取数据    			  
	* @param   	Write_Addr    AT24C02内部存储单元地址
	* @return   Byte  	读取的数据
	* Sample usage:AT24C02_Random_Read(1);
    */
uint8_t AT24C02_Random_Read(uint8_t Write_Addr)
{
	uint8_t Byte = 0;
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR);
	I2C_Receive_Ack();
	I2C_Write_Byte(Write_Addr);
	I2C_Receive_Ack();
	
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR | 0x01);
	I2C_Receive_Ack();
	Byte = I2C_Receive_Byte();
	I2C_Send_Ack(1);
	I2C_Stop();
	return Byte;
}

/****
	* @brief	AT24C02连续读取数据    			  
	* @param   	Write_Addr    AT24C02内部存储单元地址
	* @return   Byte  	读取的数据
    * @param   	Num     要写入的个数  0-256
	* Sample usage:AT24C02_Sequential_Read(1,arr,8);
    */
void AT24C02_Sequential_Read(uint8_t Write_Addr,uint8_t *Byte,uint16_t Num)
{
	uint16_t i = 0;
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR);
	I2C_Receive_Ack();
	I2C_Write_Byte(Write_Addr);
	I2C_Receive_Ack();
	
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDR | 0x01);
	I2C_Receive_Ack();
	for (i = 0; i <= Num; i++)
    {
		*Byte++ = I2C_Receive_Byte();
		if(Num == i)
		{
			I2C_Send_Ack(1);
		}
		else
		{
			I2C_Send_Ack(0);
		}
	}
	I2C_Stop();
}

