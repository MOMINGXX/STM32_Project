#include "EEPROM.h"

/****
	* @brief	EEPROM��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:IIC_Init();
    */
void EEPROM_Init()
{
    IIC_Init();
}

/****
	* @brief	EEPROMд��һ�ֽ�����    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
    * @param   	Byte    Ҫд�������
	* @return   ��  	
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
	* @brief	EEPROMд��һҳ����    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
    * @param   	Byte    Ҫд������ݵĵ�ַ
    * @param   	Num     Ҫд��ĸ���  0-8
	* @return   ��  	
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
	* @brief	EEPROMд������    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
    * @param   	Byte    Ҫд������ݵĵ�ַ
    * @param   	Num     Ҫд��ĸ���  0-255
	* @return   ��  	
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
	* @brief	EEPROM��ȡ����    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
	* @return   Byte  	��ȡ������
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
	* @brief	EEPROM������ȡ����    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
	* @return   Byte  	��ȡ������
    * @param   	Num     Ҫд��ĸ���  0-255
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


