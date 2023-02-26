#include "GD25Q16.h"

/****
	* @brief	GD25Q16��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:GD25Q16_Init();
    */
void GD25Q16_Init()
{
   SOFT_SPI_Config();
}

/****
	* @brief	GD25Q16 дʹ��	  
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Write_ENABLE();
    */
void GD25Q16_Write_ENABLE()
{
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_WRITE_ENABLE);
    SPI_W_CS(1);
}

/****
	* @brief	��ȡGD25Q16 ��ID		  
	* @param   	��
	* @return   GD25Q16_ID  	GD25Q16��ID
	* Sample usage:GD25Q16_ReadID();
    */
uint32_t GD25Q16_ReadID()
{
    uint32_t GD25Q16_ID;
    SPI_W_CS(0);
	
    SOFT_SPI_SwapByte(GD25QX_JEDEC_ID);

    GD25Q16_ID = SOFT_SPI_SwapByte(DUMMY);
    GD25Q16_ID <<= 8;
    GD25Q16_ID |= SOFT_SPI_SwapByte(DUMMY);
    GD25Q16_ID <<= 8;
    GD25Q16_ID |= SOFT_SPI_SwapByte(DUMMY);
	
    SPI_W_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	�ж�GD25Q16�Ƿ�д�����  ��  �ȴ� WIP(BUSY) ��־ �� 0	  
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_WaitForWrite();
    */
void GD25Q16_WaitForWrite()
{
    SPI_W_CS(0);
	
    SOFT_SPI_SwapByte(GD25QX_READ_STATUS_REGISTER);

    while((SOFT_SPI_SwapByte(DUMMY) & 0x01) == SET);
    
    printf("\r\n%d\n",SOFT_SPI_SwapByte(DUMMY));

    SPI_W_CS(1);
}

/****
	* @brief	����GD25Q16 ����        4KB
	* @param   	Addr    Ҫ������������ַ
	* @return   ��
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Sector_Erase(uint32_t Addr)
{
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_SECTOR_ERASE);

    //���Ͳ���������ַ�ĸ�λ
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //���Ͳ���������ַ����λ
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //���Ͳ���������ַ�ĵ�λ
    SOFT_SPI_SwapByte(Addr & 0xFF);

	SPI_W_CS(1);
    GD25Q16_WaitForWrite();
}

/****
	* @brief	���� GD25Q16 
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Chip_Erase();
    */
void GD25Q16_Chip_Erase()
{
    GD25Q16_Write_ENABLE();

    SPI_W_CS(0);

    SOFT_SPI_SwapByte(GD25QX_CHIP_ERASE);

	SPI_W_CS(1);
    GD25Q16_WaitForWrite();
}

/****
	* @brief	��ȡGD25Q16 ����
	* @param   	Addr    ��ȡ�ĵ�ַ
    * @param   	Data    �洢��ȡ������
    * @param   	Num     ��ȡ���ݵĳ���
	* @return   ��
	* Sample usage:GD25Q16_Read_Data(0,buff,4096);
    */
void GD25Q16_Read_Data(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
	SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_READ_DATA);

    //���Ͳ���������ַ�ĸ�λ
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //���Ͳ���������ַ����λ
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //���Ͳ���������ַ�ĵ�λ
    SOFT_SPI_SwapByte(Addr & 0xFF);

    while(Num--)
    {
        *Data++ = SOFT_SPI_SwapByte(DUMMY);
    }

	SPI_W_CS(1);
}

/****
	* @brief	GD25Q16 ҳд������
	* @param   	Addr    ��ȡ�ĵ�ַ
    * @param   	Data    Ҫд�������
    * @param   	Num     д�����ݵĳ���	1-256
	* @return   ��
	* Sample usage:GD25Q16_Page_Program(0,buff,256);
    */
void GD25Q16_Page_Program(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
	SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_PAGE_PROGRAM);

    //���Ͳ���������ַ�ĸ�λ
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //���Ͳ���������ַ����λ
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //���Ͳ���������ַ�ĵ�λ
    SOFT_SPI_SwapByte(Addr & 0xFF);

    while(Num--)
    {
        SOFT_SPI_SwapByte(*Data);
		Data++;
    }

	SPI_W_CS(1);
    GD25Q16_WaitForWrite();
}

/****
	* @brief	GD25Q16 д������
	* @param   	Addr    ��ȡ�ĵ�ַ
    * @param   	Data    Ҫд�������
    * @param   	Num     д�����ݵĳ���	
	* @return   ��
	* Sample usage:GD25Q16_Buff_Write(0,buff,256);
    */
void GD25Q16_Buff_Write(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr_Temp = 0, count = 0, temp = 0;
    /*mod�������࣬��Addr��GD25QX_PageSize��������������Addr_TempֵΪ0*/
    Addr_Temp = Addr % GD25QX_PageSize;
	
	/*��count������ֵ���պÿ��Զ��뵽ҳ��ַ*/
    count = GD25QX_PageSize - Addr_Temp;
	/*�����Ҫд��������ҳ*/
    NumOfPage =  Num / GD25QX_PageSize;
	/*mod�������࣬�����ʣ�಻��һҳ���ֽ���*/
    NumOfSingle = Num % GD25QX_PageSize;
	
	/* Addr_Temp=0,��WriteAddr �պð�ҳ���� aligned  */
    if (Addr_Temp == 0)
    {
        /* Num < GD25QX_PageSize */
        if (NumOfPage == 0) 
        {
            GD25Q16_Page_Program(Addr,Data,Num);
        }
        else /* Num > GD25QX_PageSize */
        { 
            /*�Ȱ�����ҳ��д��*/
            while (NumOfPage--)
            {
                GD25Q16_Page_Program(Addr,Data,GD25QX_PageSize);
                Addr += GD25QX_PageSize;
                Data += GD25QX_PageSize;
            }
            /*���ж���Ĳ���һҳ�����ݣ�����д��*/
            GD25Q16_Page_Program(Addr,Data,NumOfSingle);
        }
    }
    /* ����ַ�� GD25QX_PageSize ������  */
    else 
    {
        /* Num < GD25QX_PageSize */
        if (NumOfPage == 0)
        {
            /*��ǰҳʣ���count��λ�ñ�NumOfSingleС��һҳд����*/
            if (NumOfSingle > count) 
            {
                temp = NumOfSingle - count;
                 /*��д����ǰҳ*/
                GD25Q16_Page_Program(Addr,Data,count);
                        
                Addr +=  count;
                Data += count;
                /*��дʣ�������*/
                GD25Q16_Page_Program(Addr,Data,temp);
            }
            else /*��ǰҳʣ���count��λ����д��NumOfSingle������*/
            {
                GD25Q16_Page_Program(Addr,Data,Num);
            }
        }
        else /* Num > GD25QX_PageSize */
        {
            /*��ַ����������count�ֿ������������������*/
            Num -= count;
            NumOfPage = Num / GD25QX_PageSize;
            NumOfSingle = Num % GD25QX_PageSize;
                    
            /* ��д��count�����ݣ�Ϊ��������һ��Ҫд�ĵ�ַ���� */
            GD25Q16_Page_Program(Addr,Data,count);
                    
            /* ���������ظ���ַ�������� */
            Addr +=  count;
            Data += count;
                /*������ҳ��д��*/
            while (NumOfPage--)
            {
                GD25Q16_Page_Program(Addr,Data,GD25QX_PageSize);
                Addr += GD25QX_PageSize;
                Data += GD25QX_PageSize;
            }
            /*���ж���Ĳ���һҳ�����ݣ�����д��*/
            if (NumOfSingle != 0)
            {
                GD25Q16_Page_Program(Addr,Data,NumOfSingle);
            }
        }
    }
}

/****
	* @brief	GD25Q16 ��λ
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_RESET();
    */
void GD25Q16_RESET()
{
    GD25Q16_WaitForWrite();
    //��λʹ��
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_ENABLE_RESET);
    SPI_W_CS(1);
    //��λ
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_RESET);
    SPI_W_CS(1);
    //�豸����Ҫ��ԼtRST=60?s������
    Delay_us(60);
}

/****
	* @brief	GD25Q16 �������ģʽ
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Power_Down();
    */
void GD25Q16_Power_Down()   
{ 
    SPI_W_CS(0);

    //���� ���� ����
    SOFT_SPI_SwapByte(GD25QX_POWER_DOWN);

    SPI_W_CS(1);
}   

/****
	* @brief	���� GD25Q16
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_WAKE_UP() ;
    */
void GD25Q16_WAKE_UP()   
{
    SPI_W_CS(0);

    //���� �ϵ� ���� */
    SOFT_SPI_SwapByte(GD25QX_RELEASE_POWER_DOWN);

    SPI_W_CS(1);
}
