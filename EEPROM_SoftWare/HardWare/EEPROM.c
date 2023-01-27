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
	Delay_ms(2);
}

#if 0
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
    Delay_ms(2);
}
#else
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
    while(Num--)
    {
        EEPROM_Byte_Write(Addr++,*Byte++);
        Delay_ms(2);
    }
}
#endif

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
    IIC_Stop();
    return Byte;
}

/****
	* @brief	EEPROM������ȡ����    			  
	* @param   	Addr    EEPROM�ڲ��洢��Ԫ��ַ
	* @return   Byte  	��ȡ������
    * @param   	Num     Ҫд��ĸ���  
	* Sample usage:EEPROM_Sequential_Read(1,arr,8);
    */
void EEPROM_Sequential_Read(uint8_t Addr,uint8_t *Byte,uint8_t Num)
{
    while(Num--)
    {
        *Byte++ = EEPROM_Random_Read(Addr++);
    }
}


