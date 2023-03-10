#include "NRF24L01.h"

/* uint8_t NRF24L01_RX_BUF[NRF24L01_RX_PLOAD_WIDTH];		//接收数据缓存
uint8_t NRF24L01_TX_BUF[NRF24L01_TX_PLOAD_WIDTH];		//发射数据缓存 */
const uint8_t NRF24L01_TX_ADDRESS[NRF24L01_TX_ADR_WIDTH] = {0x00,0xc2,0xc2,0xc2,0xc2};  // 定义一个静态发送地址
const uint8_t NRF24L01_RX_ADDRESS[NRF24L01_RX_ADR_WIDTH] = {0x00,0xc2,0xc2,0xc2,0xc2};

/****
	* @brief	NRF24L01引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:NRF24L01_GPIO_Config();
    */
static void NRF24L01_GPIO_Config()
{
	P1M0 &= ~0x40; 
	P1M1 &= ~0x40; 		//P16为准双向口 

    P0M0 &= ~0x08; 
	P0M1 &= ~0x08; 		//P03为准双向口 

	NRF24L01_CE = 1;
}

/****
	* @brief	NRF24L01初始化 
	* @param   	无
	* @return   无 	
	* Sample usage:NRF24L01_Init();
    */
void NRF24L01_Init()
{
    NRF24L01_GPIO_Config();
    SPI_Init();
}

/****
	* @brief    NRF24L01 向特定的寄存器写入数据 	  
	* @param   	Reg: NRF24L01 的命令 + 寄存器地址
	* @param    Data: 向寄存器写入的数据 
    * @return   Status：寄存器的状态
	* Sample usage:NRF24L01_WriteReg(NOP,NOP);
    */
static uint8_t NRF24L01_WriteReg(uint8_t Reg,uint8_t Data)
{
    uint8_t Status;
    SPI_CS = 0;
    Status = SPI_Send_ReceiveByte(Reg);
    SPI_Send_ReceiveByte(Data);
    SPI_CS = 1;
    return Status;
}

/****
	* @brief    NRF24L01 向特定的寄存器读数据 	  
	* @param   	Reg: NRF24L01 的命令 + 寄存器地址
    * @return   Data：寄存器中的数据
	* Sample usage:NRF24L01_ReadReg(NOP);
    */
static uint8_t NRF24L01_ReadReg(uint8_t Reg)
{
    uint8_t Data;
    SPI_CS = 0;
    SPI_Send_ReceiveByte(Reg);
    Data = SPI_Send_ReceiveByte(NRF24L01_NOP);
    SPI_CS = 1;
    return Data;
}

/****
	* @brief    NRF24L01 向特定的寄存器写入多个数据 	  
	* @param   	Reg: NRF24L01 的命令 + 寄存器地址
	* @param    Buff: 用于存储要写入寄存器数据的数组
    * @param    Len: Buff的数据长度
    * @return   Status：寄存器的状态
	* Sample usage:NRF24L01_WriteBuff(NOP,NOP,6);
    */
static uint8_t NRF24L01_WriteBuff(uint8_t Reg,uint8_t *Buff,uint8_t Len)
{
    uint8_t Status;
    uint8_t i;
    SPI_CS = 0;
    Status = SPI_Send_ReceiveByte(Reg);
    for(i = 0; i < Len; i++)
    {
        SPI_Send_ReceiveByte(*Buff++);
    }
    SPI_CS = 1;
    return Status;
}

/****
	* @brief    NRF24L01 向特定的寄存器读多个数据 	  
	* @param   	Reg: NRF24L01 的命令 + 寄存器地址
    * @return   Buff：用于存储被读出寄存器数据的数组
    * @param    Len: Buff的数据长度
    * @return   Status：寄存器的状态
	* Sample usage:NRF24L01_ReadBuff(Reg,Buff,6);
    */
static uint8_t NRF24L01_ReadBuff(uint8_t Reg,uint8_t *Buff,uint8_t Len)
{
    uint8_t Status;
    uint8_t i;
    SPI_CS = 0;
    SPI_Send_ReceiveByte(Reg);
    for(i = 0; i < Len; i++)
    {
        *Buff++ = SPI_Send_ReceiveByte(NRF24L01_NOP);
    }
    SPI_CS = 1;
    return Status;
}

/****
	* @brief    检测NRF24L01是否存在  
	* @param   	无
    * @return   SUCCESS   成功
    *           ERROR     失败
	* Sample usage:NRF24L01_Check();
    */
uint8_t NRF24L01_Check()
{
	uint8_t Tx_Buff[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
	uint8_t Rx_Buff[5] = { 0 };
	uint8_t i; 
	 
	//写入5个字节的地址
	NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_TX_ADDR,Tx_Buff,5);
	//读出写入的地址 
	NRF24L01_ReadBuff(NRF24L01_TX_ADDR,Rx_Buff,5); 
	 
	//比较             
	for(i = 0; i < 5; i++)
	{
		if(Tx_Buff[i] != Rx_Buff[i])
		break;
	} 
	       
	if(i != 5)
		return ERROR ;        //MCU与NRF24L01连接失败
	else
		return SUCCESS ;      //MCU与NRF24L01正常连接
}

/****
	* @brief    NRF24L01 配置接收模式  
	* @param   	无
    * @return   无
	* Sample usage:NRF24L01_RX_Mode();
    */
void NRF24L01_RX_Mode()
{
	NRF24L01_CE = 0;

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,NRF24L01_RX_ADR_WIDTH);//写RX节点地址
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_AA,0x01);    //使能通道0的自动应答    
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_RXADDR,0x01);//使能通道0的接收地址  //NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_SETUP_RETR,0x1A);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_CH,NRF24L01_CHANAL);      //设置RF通信频率    
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RX_PW_P0,NRF24L01_RX_PLOAD_WIDTH);//选择通道0的有效数据宽度      
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_SETUP,0x0f); //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_CONFIG, 0x0f);  //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
 
	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,0xff);	//清楚所有中断标志位
	   
    NRF24L01_CE = 1;
}  

/****
	* @brief    NRF24L01 配置发送模式
	* @param   	无
    * @return   无
	* Sample usage:NRF24L01_TX_Mode();
    */
void NRF24L01_TX_Mode()
{  
	NRF24L01_CE = 0;

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_TX_ADDR,(uint8_t*)NRF24L01_TX_ADDRESS,NRF24L01_TX_ADR_WIDTH);    //写TX节点地址 

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,NRF24L01_RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK   

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_AA,0x01);     //使能通道0的自动应答    

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_RXADDR,0x01); //使能通道0的接收地址  

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_CH,NRF24L01_CHANAL);       //设置RF通道为CHANAL

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发射模式,开启所有中断

	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,0xff);	//清楚所有中断标志位
	
	Delay_ms(150);
    /*CE拉高，进入发送模式*/	
    NRF24L01_CE = 1;
}

/****
	* @brief    NRF24L01 发送一次数据	  
    * @return   TxBuff    待发送的数据首地址
    * @return   NRF24L01_TX_DS  发送完成
    *           NOP     错误代码
	* Sample usage:NRF24L01_TxPacket(Buff);
    */
uint8_t NRF24L01_TxPacket(uint8_t *TxBuff)
{
	uint8_t Status;
	NRF24L01_CE = 0;
    NRF24L01_WriteBuff(NRF24L01_W_TX_PAYLOAD,TxBuff,NRF24L01_TX_PLOAD_WIDTH); //写数据到 BUFF  32个字节
    NRF24L01_CE = 1;

    while(RESET != NRF24L01_IRQ);                 //等待发送完成
    Status = NRF24L01_ReadReg(NRF24L01_STATUS);     //读取状态寄存器的值	   
	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,Status);  //清除TX_DS或MAX_RT中断标志
	if(Status & NRF24L01_MAX_RT)                   //达到最大重发次数
	{
		NRF24L01_WriteReg(NRF24L01_FLUSH_TX,0xFF); //清除TX FIFO寄存器 
		return NRF24L01_MAX_RT; 
	}
	if(Status & NRF24L01_TX_DS)//发送完成
	{
		return NRF24L01_TX_DS;
	}
	return 0xFF;                 //其他原因发送失败
} 

/****
	* @brief    NRF24L01 接收一次数据	  
    * @return   RxBuff  待接收的数据首地址
    * @return   0  收到数据
    *           1  没收到任何数据
	* Sample usage:NRF24L01_RxPacket(Buff);
    */
uint8_t NRF24L01_RxPacket(uint8_t *RxBuff)
{
	uint8_t Status; 
	if(RESET == NRF24L01_IRQ)
	{
		/*读取Status寄存器的值  */               
		Status = NRF24L01_ReadReg(NRF24L01_STATUS);
		//printf("Status:0x%x\n",Status);
		/* 清除中断标志*/      
		NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,Status);

		/*判断是否接收到数据*/
		if(Status & NRF24L01_RX_DR)                                 //接收到数据
		{
			NRF24L01_ReadBuff(NRF24L01_R_RX_PAYLOAD,RxBuff,NRF24L01_RX_PLOAD_WIDTH);//读取数据
			NRF24L01_WriteReg(NRF24L01_FLUSH_RX,0xFF);               //清除RX FIFO寄存器
			return 0; 
		}
	}
	return 1;                    //没收到任何数据
}

/****
	* @brief    检测NRF24L01是否存在  并打印信息
	* @param   	无
    * @return   无
	* Sample usage:NRF24L01_Check_detection();
    */
void NRF24L01_Check_detection()
{
	while(NRF24L01_Check() != SUCCESS)
	{
		printf("NRF24L01_Check failed !");
		printf("\n");
		Delay_ms(1000);
	}
	printf("NRF24L01_Check succeed !");
	printf("\n");
}
