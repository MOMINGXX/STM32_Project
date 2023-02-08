#include "GD25Q16.h"

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;    
//static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/****
	* @brief	GD25Q16��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:GD25Q16_Init();
    */
void GD25Q16_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    GD25Q16_SPI_APBxCLKCMD(GD25Q16_SPI_CLK,ENABLE);                //����SPIʱ��
    GD25Q16_SPI_GPIO_APBxCLKCMD(GD25Q16_SPI_GPIO_CLK,ENABLE);      //����SPI_GPIOʱ��

    //��ʼ��GPIO
    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_CS_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;          //����1���
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GD25Q16_SPI_CS_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_SCK_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;            //���츴�����
    GPIO_Init(GD25Q16_SPI_SCK_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_MISO_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //��������
    GPIO_Init(GD25Q16_SPI_MISO_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_MOSI_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;            //���츴�����
    GPIO_Init(GD25Q16_SPI_MOSI_GPIO_PORT,&GPIO_InitStruct);

    GD25Q16_SPI_CS(1);

    //��ʼ��SPI
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;     //������Ԥ��Ƶֵ
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                           //(ʱ����λ)�ڶ��������أ��������أ����ݱ�����
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                            //(ʱ�Ӽ���)����״̬Ϊ�ߵ�ƽ
    SPI_InitStruct.SPI_CRCPolynomial = 7;                               //CRCУ��  ��ʹ��
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                      //����֡��СΪ8λ
    SPI_InitStruct.SPI_Direction = SPI_Mode_Master;                     //Ϊ����
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                     //���ݴ���� MSB λ��ʼ
    SPI_InitStruct.SPI_Mode = SPI_Direction_2Lines_FullDuplex ;         //SPI ����Ϊ˫��˫��ȫ˫��
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                              //�ڲ� NSS �ź��� SSI λ����
    SPI_Init(GD25Q16_SPI,&SPI_InitStruct);

    //ʹ��SPI
    SPI_Cmd(GD25Q16_SPI,ENABLE);
}

/****
	* @brief	GD25Q16��������    			  
	* @param   	Byte    ���͵�����
	* @return   SPI_I2S_ReceiveData(GD25Q16_SPI)  	��ȡGD25Q16������
	* Sample usage:GD25Q16_Send_Byte(DUMMY);
    */
uint8_t GD25Q16_Send_Byte(uint8_t Byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;
    //��鲢�ȴ����ͻ�����Ϊ��
    while(RESET == SPI_I2S_GetFlagStatus(GD25Q16_SPI,SPI_I2S_FLAG_TXE))
    {
        if((SPITimeout--) == 0) {return W25QX_ERROR(1);}
    }
    //д�����ݵ�������
    SPI_I2S_SendData(GD25Q16_SPI,Byte);
    //��鲢�ȴ����ջ�����Ϊ��
    while(RESET == SPI_I2S_GetFlagStatus(GD25Q16_SPI,SPI_I2S_FLAG_RXNE))
    {
        if((SPITimeout--) == 0) {return W25QX_ERROR(2);}
    }
    //��������
    return SPI_I2S_ReceiveData(GD25Q16_SPI);
}

/****
	* @brief	��ȡGD25Q16 ��ID	    0xC84015	  
	* @param   	��
	* @return   GD25Q16_ID  	GD25Q16��ID
	* Sample usage:GD25Q16_Read_JEDEC_ID();
    */
uint32_t GD25Q16_Read_JEDEC_ID()
{
    uint32_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //���Ͷ� JEDEC_ID ָ��
    GD25Q16_Send_Byte(GD25QX_JEDEC_ID);

    //MANUFACTURER ID      ��ʶ
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY) << 16;
    //�豸ID  ��λ
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY) << 8;
    //�豸ID  ��λ
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	��ȡGD25Q16 ���豸ID		  14
	* @param   	��
	* @return   GD25Q16_ID  	GD25Q16��ID
	* Sample usage:GD25Q16_Read_Device_ID();
    */
uint8_t GD25Q16_Read_Device_ID()
{
    uint8_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //���Ͷ� JEDEC_ID ָ��
    GD25Q16_Send_Byte(GD25QX_DEVICE_ID);

    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    //�豸ID  
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	��ȡGD25Q16 �ĳ���ID �� �豸ID		  C8  14
	* @param   	��
	* @return   GD25Q16_ID  	GD25Q16��ID
	* Sample usage:GD25Q16_Read_Manufacture_ID();
    */
uint16_t GD25Q16_Read_Manufacture_ID()
{
    uint16_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //���Ͷ� JEDEC_ID ָ��
    GD25Q16_Send_Byte(GD25QX_ManufactDeviceID);

    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    //MANUFACTURER ID      ��ʶ
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY) << 16;
    //�豸ID  
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
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
    GD25Q16_SPI_CS(0);
    //���Ͷ� ���� ָ��
    GD25Q16_Send_Byte(GD25QX_READ_DATA);

    //��ַ��λ
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //��ַ��λ
    GD25Q16_Send_Byte(Addr & 0xFF);
    
    while(Num--)
    {
        //��ȡ����
        *Data++ = GD25Q16_Send_Byte(DUMMY);
    }

    GD25Q16_SPI_CS(1);
}

/****
	* @brief	GD25Q16 дʹ��	  
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Write_ENABLE();
    */
void GD25Q16_Write_ENABLE()
{
    GD25Q16_SPI_CS(0);
    //���� дʹ�� ָ��
    GD25Q16_Send_Byte(GD25QX_WRITE_ENABLE);

    GD25Q16_SPI_CS(1);
}

/****
	* @brief	�ж�GD25Q16�Ƿ�д�����  ��  �ȴ� WIP(BUSY) ��־ �� 0	  
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_WaitForWrite();
    */
void GD25Q16_WaitForWrite()
{
    uint8_t Reg_Status = 0;
    GD25Q16_SPI_CS(0);
    //���Ͷ� �Ĵ���״̬ ָ��
    GD25Q16_Send_Byte(GD25QX_READ_STATUS_REGISTER);

    do
    {
        Reg_Status =GD25Q16_Send_Byte(DUMMY);
    } while ((Reg_Status & 0x01) == SET);
    
    GD25Q16_SPI_CS(1);
}


/****
	* @brief	����GD25Q16 ����        4 KB(4096 Byte)
	* @param   	Addr    Ҫ������������ַ
	* @return   ��
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Sector_Erase(uint32_t Addr)
{
    Addr *= 4096;
    //дʹ��
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    GD25Q16_SPI_CS(0);
    
    //���� �������� ָ��
    GD25Q16_Send_Byte(GD25QX_SECTOR_ERASE);

    //����������λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //����������λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //����������λ��ַ
    GD25Q16_Send_Byte(Addr & 0xFF);

    GD25Q16_SPI_CS(1);
    //�ȴ��������
    //GD25Q16_WaitForWrite();
}

/****
	* @brief	����GD25Q16 ��        32KB
	* @param   	Addr    Ҫ�����Ŀ��ַ
	* @return   ��
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Block_Erase(uint32_t Addr)
{
    //дʹ��
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    GD25Q16_SPI_CS(0);
    
    //���� ����� ָ��
    GD25Q16_Send_Byte(GD25QX_BLOCK_ERASE1);

    //���Ϳ��λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //���Ϳ���λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //���Ϳ��λ��ַ
    GD25Q16_Send_Byte(Addr & 0xFF);

    GD25Q16_SPI_CS(1);
    //�ȴ��������
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
    //дʹ��
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();

    GD25Q16_SPI_CS(0);

    //���� Ƭ���� ָ��
    GD25Q16_Send_Byte(GD25QX_CHIP_ERASE);

	GD25Q16_SPI_CS(1);
    GD25Q16_WaitForWrite();
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
	//дʹ��
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();

    GD25Q16_SPI_CS(0);

    //���� ҳд�� ָ��
    GD25Q16_Send_Byte(GD25QX_PAGE_PROGRAM);
	
	//���Ϳ��λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //���Ϳ���λ��ַ
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //���Ϳ��λ��ַ
    GD25Q16_Send_Byte(Addr & 0xFF);
	
	while(Num--)
	{
		//д������
		GD25Q16_Send_Byte(*Data++);
	}

	GD25Q16_SPI_CS(1);
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
	* @brief	GD25Q16 �������ģʽ
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Power_Down();
    */
void GD25Q16_Power_Down()
{
    GD25Q16_SPI_CS(0);
    GD25Q16_Send_Byte(GD25QX_POWER_DOWN);  
    GD25Q16_SPI_CS(1);
}

/****
	* @brief	���� GD25Q16
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_WAKE_UP() ;
    */
void GD25Q16_WAKE_UP()  
{
    GD25Q16_SPI_CS(0);
    GD25Q16_Send_Byte(GD25QX_RELEASE_POWER_DOWN);  
    GD25Q16_SPI_CS(1);
}

/****
	* @brief	�ȴ���ʱ�ص�����
	* @param   	��
	* @return   ��
	* Sample usage:GD25Q16_Read_Data(0,buff,4096);
    */
   /*
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    //�ȴ���ʱ��Ĵ���,���������Ϣ 
    W25QX_ERROR("�ȴ���ʱ!errorCode = %d",errorCode);
    return 0;
}
*/