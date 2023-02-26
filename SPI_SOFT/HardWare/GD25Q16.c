#include "GD25Q16.h"

/****
	* @brief	GD25Q16初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage:GD25Q16_Init();
    */
void GD25Q16_Init()
{
   SOFT_SPI_Config();
}

/****
	* @brief	GD25Q16 写使能	  
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Write_ENABLE();
    */
void GD25Q16_Write_ENABLE()
{
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_WRITE_ENABLE);
    SPI_W_CS(1);
}

/****
	* @brief	读取GD25Q16 的ID		  
	* @param   	无
	* @return   GD25Q16_ID  	GD25Q16的ID
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
	* @brief	判断GD25Q16是否写入完成  及  等待 WIP(BUSY) 标志 置 0	  
	* @param   	无
	* @return   无
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
	* @brief	擦除GD25Q16 扇区        4KB
	* @param   	Addr    要擦除的扇区地址
	* @return   无
	* Sample usage:GD25Q16_Sector_Erase(0);
    */
void GD25Q16_Sector_Erase(uint32_t Addr)
{
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_SECTOR_ERASE);

    //发送擦除扇区地址的高位
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //发送擦除扇区地址的中位
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //发送擦除扇区地址的低位
    SOFT_SPI_SwapByte(Addr & 0xFF);

	SPI_W_CS(1);
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
    GD25Q16_Write_ENABLE();

    SPI_W_CS(0);

    SOFT_SPI_SwapByte(GD25QX_CHIP_ERASE);

	SPI_W_CS(1);
    GD25Q16_WaitForWrite();
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
	SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_READ_DATA);

    //发送擦除扇区地址的高位
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //发送擦除扇区地址的中位
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //发送擦除扇区地址的低位
    SOFT_SPI_SwapByte(Addr & 0xFF);

    while(Num--)
    {
        *Data++ = SOFT_SPI_SwapByte(DUMMY);
    }

	SPI_W_CS(1);
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
    GD25Q16_Write_ENABLE();
    GD25Q16_WaitForWrite();
	SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_PAGE_PROGRAM);

    //发送擦除扇区地址的高位
    SOFT_SPI_SwapByte((Addr & 0xFF0000) >> 16);
    //发送擦除扇区地址的中位
    SOFT_SPI_SwapByte((Addr & 0xFF00) >> 8);
    //发送擦除扇区地址的低位
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
	* @brief	GD25Q16 复位
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_RESET();
    */
void GD25Q16_RESET()
{
    GD25Q16_WaitForWrite();
    //复位使能
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_ENABLE_RESET);
    SPI_W_CS(1);
    //复位
    SPI_W_CS(0);
    SOFT_SPI_SwapByte(GD25QX_RESET);
    SPI_W_CS(1);
    //设备将需要大约tRST=60?s来重置
    Delay_us(60);
}

/****
	* @brief	GD25Q16 进入掉电模式
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_Power_Down();
    */
void GD25Q16_Power_Down()   
{ 
    SPI_W_CS(0);

    //发送 掉电 命令
    SOFT_SPI_SwapByte(GD25QX_POWER_DOWN);

    SPI_W_CS(1);
}   

/****
	* @brief	唤醒 GD25Q16
	* @param   	无
	* @return   无
	* Sample usage:GD25Q16_WAKE_UP() ;
    */
void GD25Q16_WAKE_UP()   
{
    SPI_W_CS(0);

    //发送 上电 命令 */
    SOFT_SPI_SwapByte(GD25QX_RELEASE_POWER_DOWN);

    SPI_W_CS(1);
}
