#include "USART.h"

uint8_t DAT1;				//存放接收的字符
uint8_t RX1_BUFF[10];		//接收的数据	缓冲区
uint8_t RX1_DAT[10];		//存放接收的数据
uint8_t RX1_COUNT=0;		//接收计数
bit Flag1 = 0;				//标志位

uint8_t RX2_BUFF[LENTH];		//接收的数据	缓冲区
uint8_t Flag3 = 0;				//标志位

/****
	* @brief	串口引脚配置	 准双向口  		  
	* @param   	无
	* @return   无 	
	* Sample usage:Uart_GPIO_Config()；
    */
static void Uart_GPIO_Config()
{
    P3M1 &= ~0x03;   
    P3M0 &= ~0x03; 		//P30 P31双向IO口
	
	P0M1 &= ~0x03;   
    P0M0 &= ~0x03; 		//P00 P01双向IO口
}

/****
	* @brief	串口1 配置	   		  
	* @param   	无
	* @return   无 	
	* Sample usage:Uart_Config();
    */
static void Uart1_Config()	
{
    
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = BRT;			//设置定时初始值
	T2H = BRT >> 8;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时    
    IP |= 0x00;
    IPH |= 0x10;        //优先级2
    ES = 1;         	//开启串口1中断
}

/****
	* @brief	串口3 配置	   		  
	* @param   	无
	* @return   无 	
	* Sample usage:Uart_Config();
    */
static void Uart3_Config()	
{
	S3CON = 0x10;			//8位数据,可变波特率
	T2x12 = 1;				//定时器时钟1T模式
	T2L = BRT;				//设置定时初始值
	T2H = BRT >> 8;			//设置定时初始值
	T2R = 1;				//定时器2开始计时    
    IP3 |= 0x00;	
    IP3H |= 0x00;       	//优先级
    ES3 = 1;         		//开启串口3中断
}

/****
	* @brief	串口初始化	   		  
	* @param   	无
	* @return   无  	
	* Sample usage:Usart_Init();
    */
void Usartx_Init()	
{
    Uart_GPIO_Config();
    Uart1_Config();	
	Uart3_Config();
}

/****
	* @brief	串口发送一个字节	   		  
	* @param   	Byte	要发送的字节  
	* @return   无  	
	* Sample usage:Uart_SendByte(0x45);  
    */
void Usartx_SendByte(USART_TypeDef USARTx,uint8_t Byte)
{
	switch(USARTx)
	{
		case USART1:
			SBUF = Byte;
			while(!(SCON & 0x02));	//等待发送完毕 TI置1
			SCON &= ~0x02;			//软件置0
		break;
		case USART3:
			S3BUF = Byte;
			while(!(S3CON & 0x02));	//等待发送完毕 TI置1
			S3CON &= ~0x02;			//软件置0
		break;
	}
}

/****
	* @brief	串口发送一个字符串 
    * @param    String	要发送的字符串 
	* @return   无        	
	* Sample usage:Uart_SendString("ABCD"); 
    */
void Usartx_SendString(USART_TypeDef USARTx,uint8_t *String)
{
    while(*String != '\0')
    {
        Usartx_SendByte(USARTx,*String++);
    }
}

/****
	* @brief    串口发送数组
	* @param   	Buf     要发送的数组 
	* @param   	Len		数组长度
	* @return   无        	
	* Sample usage:Uart_SendString(arr,sizeof(arr)/sizeof(arr[0]));    
	*/
void Usartx_SendBuff(USART_TypeDef USARTx,uint8_t *Buff,uint16_t Len)
{
	while(Len--)
	{
		Usartx_SendByte(USARTx,*Buff++);
	}
}

/****
	* @brief	平方计算  			  
    * @param   	X   基值
    * @param    Y   指数的值
	* @return   Result   x 的 y 次幂的结果	
	* Sample usage: Usart_Pow(10,Length);
    */
static uint32_t Usartx_Pow(uint32_t X, uint32_t Y)
{
    //X^Y
    uint32_t Result = 1;
    while(Y--)
    {
        Result *= X;
    }
    return Result;
}

/****
	* @brief	串口发送数字  			  
    * @param   	Number  要发送的数字
    * @param    Length  数字的长度
	* @return   无  	
	* Sample usage: Usart_SendNumber(12345,5);
    */
void Usartx_SendNumber(USART_TypeDef USARTx,uint32_t Number,uint8_t Length)
{
    while(Length--)
    {
        Usartx_SendByte(USARTx,Number / Usartx_Pow(10,Length) % 10 + '0'); //23 2 3
    }
}

void Usartx_sprintf(USART_TypeDef USARTx,char *format, ...)
{
    char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Usartx_SendString(USARTx,String);
}

/****
	@brief      printf打印
	@param   	c
	@return     c        	
	Sample usage:  printf("Hello\n"); 
****/
#if (PRINTF_SELECT == 1)
int8_t putchar(int8_t c)
{
	if(c == '\n')
	{
		Usartx_SendByte(USART1,0x0D);
	}
	Usartx_SendByte(USART1,c);
	return c;
}

#elif (PRINTF_SELECT == 3)

int8_t putchar(int8_t c)
{
	if(c == '\n')
	{
		Usartx_SendByte(USART3,0x0D);
	}
	Usartx_SendByte(USART3,c);
	return c;
}
#endif

void Uart1_Routine() interrupt 4
{
	static uint8_t i = 1;
	if(SCON & 0x01)
	{
		SCON &= ~0x01;
		DAT1 = SBUF;
		if(DAT1 != '#')				//'#'结束标志
		{
			RX1_BUFF[RX1_COUNT++] = DAT1++;
		}
		else
		{
			for(i=0;i<RX1_COUNT;i++)
			{
				RX1_DAT[i] = RX1_BUFF[i];
			}
			RX1_COUNT=0;
			Flag1=1;
		}
	}
}

static uint8_t Usart3_ReceivePacket(uint8_t Usart3_RxData,uint8_t *RX2_BUFF)
{
	static uint8_t RxState = 0;
	static uint8_t i = 1;
	switch(RxState)
	{
		case 0:
		if(0xA5 == Usart3_RxData)
		{
			RxState = 1;
			RX2_BUFF[0] = Usart3_RxData;
		}
		else RxState = 0;
		break;
		case 1:
		RX2_BUFF[i] = Usart3_RxData;
		i++;
		if(i >= LENTH)
		{
			i = 1;
			RxState = 0;
			return SUCCESS;
		}
		break;
		default:
			break;
	}
	return ERROR;
}

void Usart3_Routine() interrupt 17
{
	uint8_t Usart3_RxData = 0;
	
	if(S3CON & 0x01)
	{
		S3CON &= ~0x01;
		Usart3_RxData = S3BUF;
		Flag3 = Usart3_ReceivePacket(Usart3_RxData,RX2_BUFF);
	}
}



//void Uart3_Routine() interrupt 17
//{
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	uint8_t RxData = 0;
//	
//	if(S3CON & 0x01)
//	{
//		S3CON &= ~0x01;
//		RxData = S3BUF;
//		if(0 == RxState)
//		{
//			if(0xA5 == RxData)
//			{
//				RxState = 1;
//				pRxPacket = 0 ;
//			}
//		}
//		else if(1 == RxState)
//		{
//			if(0x5A == RxData)
//			{
//				RxState = 2;
//			}
//			else
//			{
//				RX2_BUFF[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if (2 == RxState)
//		{
//			RxState = 0;
//			Flag3 = 1;
//		}
//	}
//}

