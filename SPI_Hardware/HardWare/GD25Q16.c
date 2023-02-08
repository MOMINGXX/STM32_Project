#include "GD25Q16.h"

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;    
//static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/****
	* @brief	GD25Q16初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage:GD25Q16_Init();
    */
void GD25Q16_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    GD25Q16_SPI_APBxCLKCMD(GD25Q16_SPI_CLK,ENABLE);                //开启SPI时钟
    GD25Q16_SPI_GPIO_APBxCLKCMD(GD25Q16_SPI_GPIO_CLK,ENABLE);      //开启SPI_GPIO时钟

    //初始化GPIO
    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_CS_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;          //推挽1输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GD25Q16_SPI_CS_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_SCK_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;            //推挽复用输出
    GPIO_Init(GD25Q16_SPI_SCK_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_MISO_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //浮空输入
    GPIO_Init(GD25Q16_SPI_MISO_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GD25Q16_SPI_MOSI_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;            //推挽复用输出
    GPIO_Init(GD25Q16_SPI_MOSI_GPIO_PORT,&GPIO_InitStruct);

    GD25Q16_SPI_CS(1);

    //初始化SPI
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;     //波特率预分频值
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                           //(时钟相位)第二个跳变沿（即上升沿）数据被采样
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                            //(时钟极性)空闲状态为高电平
    SPI_InitStruct.SPI_CRCPolynomial = 7;                               //CRC校验  不使用
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                      //数据帧大小为8位
    SPI_InitStruct.SPI_Direction = SPI_Mode_Master;                     //为主机
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                     //数据传输从 MSB 位开始
    SPI_InitStruct.SPI_Mode = SPI_Direction_2Lines_FullDuplex ;         //SPI 设置为双线双向全双工
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                              //内部 NSS 信号有 SSI 位控制
    SPI_Init(GD25Q16_SPI,&SPI_InitStruct);

    //使能SPI
    SPI_Cmd(GD25Q16_SPI,ENABLE);
}

/****
	* @brief	GD25Q16发送数据    			  
	* @param   	Byte    发送的数据
	* @return   SPI_I2S_ReceiveData(GD25Q16_SPI)  	读取GD25Q16的数据
	* Sample usage:GD25Q16_Send_Byte(DUMMY);
    */
uint8_t GD25Q16_Send_Byte(uint8_t Byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;
    //检查并等待发送缓冲区为空
    while(RESET == SPI_I2S_GetFlagStatus(GD25Q16_SPI,SPI_I2S_FLAG_TXE))
    {
        if((SPITimeout--) == 0) {return W25QX_ERROR(1);}
    }
    //写入数据到缓冲区
    SPI_I2S_SendData(GD25Q16_SPI,Byte);
    //检查并等待接收缓冲区为空
    while(RESET == SPI_I2S_GetFlagStatus(GD25Q16_SPI,SPI_I2S_FLAG_RXNE))
    {
        if((SPITimeout--) == 0) {return W25QX_ERROR(2);}
    }
    //接收数据
    return SPI_I2S_ReceiveData(GD25Q16_SPI);
}

/****
	* @brief	读取GD25Q16 的ID	    0xC84015	  
	* @param   	无
	* @return   GD25Q16_ID  	GD25Q16的ID
	* Sample usage:GD25Q16_Read_JEDEC_ID();
    */
uint32_t GD25Q16_Read_JEDEC_ID()
{
    uint32_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //发送读 JEDEC_ID 指令
    GD25Q16_Send_Byte(GD25QX_JEDEC_ID);

    //MANUFACTURER ID      标识
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY) << 16;
    //设备ID  高位
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY) << 8;
    //设备ID  低位
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	读取GD25Q16 的设备ID		  14
	* @param   	无
	* @return   GD25Q16_ID  	GD25Q16的ID
	* Sample usage:GD25Q16_Read_Device_ID();
    */
uint8_t GD25Q16_Read_Device_ID()
{
    uint8_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //发送读 JEDEC_ID 指令
    GD25Q16_Send_Byte(GD25QX_DEVICE_ID);

    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    //设备ID  
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	读取GD25Q16 的厂商ID 和 设备ID		  C8  14
	* @param   	无
	* @return   GD25Q16_ID  	GD25Q16的ID
	* Sample usage:GD25Q16_Read_Manufacture_ID();
    */
uint16_t GD25Q16_Read_Manufacture_ID()
{
    uint16_t GD25Q16_ID;
    GD25Q16_SPI_CS(0);
    //发送读 JEDEC_ID 指令
    GD25Q16_Send_Byte(GD25QX_ManufactDeviceID);

    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    GD25Q16_Send_Byte(DUMMY);
    //MANUFACTURER ID      标识
    GD25Q16_ID = GD25Q16_Send_Byte(DUMMY) << 16;
    //设备ID  
    GD25Q16_ID |= GD25Q16_Send_Byte(DUMMY);

    GD25Q16_SPI_CS(1);
    return GD25Q16_ID;
}

/****
	* @brief	读取GD25Q16 数据
	* @param   	Addr    读取的地址
    * @param   	Data    存储读取的数据
    * @param   	Num     读取数据的长度
	* @return   无
	* Sample usage:GD25Q16_Read_Data(0,buff,4096);
    */
void GD25Q16_Read_Data(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
    GD25Q16_SPI_CS(0);
    //发送读 数据 指令
    GD25Q16_Send_Byte(GD25QX_READ_DATA);

    //地址高位
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //地址低位
    GD25Q16_Send_Byte(Addr & 0xFF);
    
    while(Num--)
    {
        //读取数据
        *Data++ = GD25Q16_Send_Byte(DUMMY);
    }

    GD25Q16_SPI_CS(1);
}

/****
	* @brief	GD25Q16 写使能	  
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Write_ENABLE();
    */
void GD25Q16_Write_ENABLE()
{
    GD25Q16_SPI_CS(0);
    //发送 写使能 指令
    GD25Q16_Send_Byte(GD25QX_WRITE_ENABLE);

    GD25Q16_SPI_CS(1);
}

/****
	* @brief	判断GD25Q16是否写入完成  及  等待 WIP(BUSY) 标志 置 0	  
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_WaitForWrite();
    */
void GD25Q16_WaitForWrite()
{
    uint8_t Reg_Status = 0;
    GD25Q16_SPI_CS(0);
    //发送读 寄存器状态 指令
    GD25Q16_Send_Byte(GD25QX_READ_STATUS_REGISTER);

    do
    {
        Reg_Status =GD25Q16_Send_Byte(DUMMY);
    } while ((Reg_Status & 0x01) == SET);
    
    GD25Q16_SPI_CS(1);
}


/****
	* @brief	擦除GD25Q16 扇区        4 KB(4096 Byte)
	* @param   	Addr    要擦除的扇区地址
	* @return   无
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Sector_Erase(uint32_t Addr)
{
    Addr *= 4096;
    //写使能
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    GD25Q16_SPI_CS(0);
    
    //发送 扇区擦除 指令
    GD25Q16_Send_Byte(GD25QX_SECTOR_ERASE);

    //发送扇区高位地址
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //发送扇区中位地址
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //发送扇区低位地址
    GD25Q16_Send_Byte(Addr & 0xFF);

    GD25Q16_SPI_CS(1);
    //等待擦除完成
    //GD25Q16_WaitForWrite();
}

/****
	* @brief	擦除GD25Q16 块        32KB
	* @param   	Addr    要擦除的块地址
	* @return   无
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Block_Erase(uint32_t Addr)
{
    //写使能
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    GD25Q16_SPI_CS(0);
    
    //发送 块擦除 指令
    GD25Q16_Send_Byte(GD25QX_BLOCK_ERASE1);

    //发送块高位地址
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //发送块中位地址
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //发送块低位地址
    GD25Q16_Send_Byte(Addr & 0xFF);

    GD25Q16_SPI_CS(1);
    //等待擦除完成
    GD25Q16_WaitForWrite();
}

/****
	* @brief	擦除 GD25Q16 
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Chip_Erase();
    */
void GD25Q16_Chip_Erase()
{
    //写使能
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();

    GD25Q16_SPI_CS(0);

    //发送 片擦除 指令
    GD25Q16_Send_Byte(GD25QX_CHIP_ERASE);

	GD25Q16_SPI_CS(1);
    GD25Q16_WaitForWrite();
}

/****
	* @brief	GD25Q16 页写入数据
	* @param   	Addr    读取的地址
    * @param   	Data    要写入的数据
    * @param   	Num     写入数据的长度	1-256
	* @return   无
	* Sample usage:GD25Q16_Page_Program(0,buff,256);
    */
void GD25Q16_Page_Program(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
	//写使能
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();

    GD25Q16_SPI_CS(0);

    //发送 页写入 指令
    GD25Q16_Send_Byte(GD25QX_PAGE_PROGRAM);
	
	//发送块高位地址
    GD25Q16_Send_Byte((Addr & 0xFF0000) >> 16);
    //发送块中位地址
    GD25Q16_Send_Byte((Addr & 0xFF00) >> 8);
    //发送块低位地址
    GD25Q16_Send_Byte(Addr & 0xFF);
	
	while(Num--)
	{
		//写入数据
		GD25Q16_Send_Byte(*Data++);
	}

	GD25Q16_SPI_CS(1);
    GD25Q16_WaitForWrite();
}


/****
	* @brief	GD25Q16 写入数据
	* @param   	Addr    读取的地址
    * @param   	Data    要写入的数据
    * @param   	Num     写入数据的长度	
	* @return   无
	* Sample usage:GD25Q16_Buff_Write(0,buff,256);
    */
void GD25Q16_Buff_Write(uint32_t Addr,uint8_t *Data,uint32_t Num)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr_Temp = 0, count = 0, temp = 0;
    /*mod运算求余，若Addr是GD25QX_PageSize整数倍，运算结果Addr_Temp值为0*/
    Addr_Temp = Addr % GD25QX_PageSize;
	
	/*差count个数据值，刚好可以对齐到页地址*/
    count = GD25QX_PageSize - Addr_Temp;
	/*计算出要写多少整数页*/
    NumOfPage =  Num / GD25QX_PageSize;
	/*mod运算求余，计算出剩余不满一页的字节数*/
    NumOfSingle = Num % GD25QX_PageSize;
	
	/* Addr_Temp=0,则WriteAddr 刚好按页对齐 aligned  */
    if (Addr_Temp == 0)
    {
        /* Num < GD25QX_PageSize */
        if (NumOfPage == 0) 
        {
            GD25Q16_Page_Program(Addr,Data,Num);
        }
        else /* Num > GD25QX_PageSize */
        { 
            /*先把整数页都写了*/
            while (NumOfPage--)
            {
                GD25Q16_Page_Program(Addr,Data,GD25QX_PageSize);
                Addr += GD25QX_PageSize;
                Data += GD25QX_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            GD25Q16_Page_Program(Addr,Data,NumOfSingle);
        }
    }
    /* 若地址与 GD25QX_PageSize 不对齐  */
    else 
    {
        /* Num < GD25QX_PageSize */
        if (NumOfPage == 0)
        {
            /*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
            if (NumOfSingle > count) 
            {
                temp = NumOfSingle - count;
                 /*先写满当前页*/
                GD25Q16_Page_Program(Addr,Data,count);
                        
                Addr +=  count;
                Data += count;
                /*再写剩余的数据*/
                GD25Q16_Page_Program(Addr,Data,temp);
            }
            else /*当前页剩余的count个位置能写完NumOfSingle个数据*/
            {
                GD25Q16_Page_Program(Addr,Data,Num);
            }
        }
        else /* Num > GD25QX_PageSize */
        {
            /*地址不对齐多出的count分开处理，不加入这个运算*/
            Num -= count;
            NumOfPage = Num / GD25QX_PageSize;
            NumOfSingle = Num % GD25QX_PageSize;
                    
            /* 先写完count个数据，为的是让下一次要写的地址对齐 */
            GD25Q16_Page_Program(Addr,Data,count);
                    
            /* 接下来就重复地址对齐的情况 */
            Addr +=  count;
            Data += count;
                /*把整数页都写了*/
            while (NumOfPage--)
            {
                GD25Q16_Page_Program(Addr,Data,GD25QX_PageSize);
                Addr += GD25QX_PageSize;
                Data += GD25QX_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            if (NumOfSingle != 0)
            {
                GD25Q16_Page_Program(Addr,Data,NumOfSingle);
            }
        }
    }
}

/****
	* @brief	GD25Q16 进入掉电模式
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Power_Down();
    */
void GD25Q16_Power_Down()
{
    GD25Q16_SPI_CS(0);
    GD25Q16_Send_Byte(GD25QX_POWER_DOWN);  
    GD25Q16_SPI_CS(1);
}

/****
	* @brief	唤醒 GD25Q16
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_WAKE_UP() ;
    */
void GD25Q16_WAKE_UP()  
{
    GD25Q16_SPI_CS(0);
    GD25Q16_Send_Byte(GD25QX_RELEASE_POWER_DOWN);  
    GD25Q16_SPI_CS(1);
}

/****
	* @brief	等待超时回调函数
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Read_Data(0,buff,4096);
    */
   /*
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    //等待超时后的处理,输出错误信息 
    W25QX_ERROR("等待超时!errorCode = %d",errorCode);
    return 0;
}
*/