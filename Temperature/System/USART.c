#include "USART.h"

uint8_t Usart_RxHEX[RXHEX_MAX];
char Usart_RxCharacter[RXCHA_MAX];
uint8_t Usart_RxFlag;

/****
	* @brief	NVIC初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage:Usart_NVIC_Init();
    */
static void Usart_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStruct;

    //优先级组配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    //配置NVIC参数
    NVIC_InitStruct.NVIC_IRQChannel=SPECIFIE_USART_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&NVIC_InitStruct);
}

/****
	* @brief	USART初始化      			  
	* @param   	无
	* @return   无  	
	* Sample usage: Usart_Init();
    */
void Usart_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    //开启GPIO时钟
    SPECIFIE_USART_GPIO_APBxCLKCMD(SPECIFIE_USART_GPIO_CLK,ENABLE);
    //开启串口时钟
    SPECIFIE_USART_GPIO_APBxCLKCMD(SPECIFIE_USART_CLK,ENABLE);

    //配置GPIO参数 TX为复用推挽输出
    GPIO_InitStruct.GPIO_Pin=SPECIFIE_USART_TX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(SPECIFIE_USART_TX_GPIO_PORT,&GPIO_InitStruct);

    //配置GPIO参数 RX浮空输入
    GPIO_InitStruct.GPIO_Pin=SPECIFIE_USART_RX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(SPECIFIE_USART_RX_GPIO_PORT,&GPIO_InitStruct);

    //配置串口参数
    //波特率配置
    USART_InitStruct.USART_BaudRate=SPECIFIE_USART_BAUDRATE;
    //硬件流控制配置
    USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    //串口模式
    USART_InitStruct.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
    //校验位配置
    USART_InitStruct.USART_Parity=USART_Parity_No;
    //停止位配置
    USART_InitStruct.USART_StopBits=USART_StopBits_1;
    //数据为配置
    USART_InitStruct.USART_WordLength=USART_WordLength_8b;
    USART_Init(SPECIFIE_USARTx ,&USART_InitStruct);

    //开启串口中断
    USART_ITConfig(SPECIFIE_USARTx,USART_IT_RXNE,ENABLE);

    //配置串口优先级
    Usart_NVIC_Init();

    //开启串口（使能）
    USART_Cmd(SPECIFIE_USARTx,ENABLE);
}

/****
	* @brief	串口发送一个8位数据      			  
	* @param   	USARTx  选择串口获串口外设      USART1, USART2, USART3, UART4 or UART5
    * @param   	Byte    发送的数据
	* @return   无  	
	* Sample usage: Usart_SendByte(SPECIFIE_USARTx,0x41);
    */
void Usart_SendByte(USART_TypeDef *USARTx,uint8_t Byte)
{
    USART_SendData(USARTx,Byte);
    while(RESET == USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
}

/****
	* @brief	串口发送一个16位数据      			  
	* @param   	USARTx  选择串口获串口外设      USART1, USART2, USART3, UART4 or UART5
    * @param   	Byte    发送的数据
	* @return   无  	
	* Sample usage: Usart_SendByte(SPECIFIE_USARTx,0x4122);
    */
void Usart_SendTwoByte(USART_TypeDef *USARTx,uint16_t Byte)
{
    uint8_t TimeH;
    uint8_t TimeL;
    TimeH = (Byte & 0xff00)>>8;
    TimeL = Byte & 0xff;
    Usart_SendByte(USARTx,TimeH);
    Usart_SendByte(USARTx,TimeL);
}

/****
	* @brief	串口发送数组   			  
	* @param   	USARTx  选择串口获串口外设      USART1, USART2, USART3, UART4 or UART5
    * @param   	Buff    发送的数组地址
    * @param    Length  数组的长度
	* @return   无  	
	* Sample usage: Usart_SendBuff(SPECIFIE_USARTx,arr,5);
    */
void Usart_SendBuff(USART_TypeDef *USARTx ,uint8_t *Buff, uint16_t Length)
{
    while(Length--)
    {
        Usart_SendByte(USARTx,*Buff++);
    }
}

/****
	* @brief	平方计算  			  
    * @param   	X        基值
    * @param    Y        指数的值
	* @return   Result   x 的 y 次幂的结果	
	* Sample usage: Usart_Pow(10,Length);
    */
static uint32_t Usart_Pow(uint32_t X, uint32_t Y)
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
	* @param   	USARTx  选择串口获串口外设      USART1, USART2, USART3, UART4 or UART5
    * @param   	Number  要发送的数字
    * @param    Length  数字的长度
	* @return   无  	
	* Sample usage: Usart_SendNumber(SPECIFIE_USARTx,12345,5);
    */
void Usart_SendNumber(USART_TypeDef *USARTx,uint32_t Number,uint8_t Length)
{
    while(Length--)
    {
        Usart_SendByte(USARTx,Number / Usart_Pow(10,Length) % 10 + '0'); //23 2 3
    }
}

/****
	* @brief	串口发送字符串    			  
	* @param   	USARTx  选择串口获串口外设      USART1, USART2, USART3, UART4 or UART5
    * @param   	String  要发送的字符串
	* @return   无  	
	* Sample usage: Usart_SendByte(SPECIFIE_USARTx,0x4122);
    */
void Usart_SendString(USART_TypeDef *USARTx,char *String)
{
    while(*String != '\0')
    {
        Usart_SendByte(USARTx,*String++);
    } 
}

//printf重定向 打印    
int fputc(int c,FILE *pf)
{
    if(c == '\n')
    {
        Usart_SendByte(SPECIFIE_USARTx,0x0D);
    }
    Usart_SendByte(SPECIFIE_USARTx,(uint8_t)c);
    return c;
}

//scanf重定向 输入
int fgetc(FILE *pf)
{
	//等待串口输入数据
	while(RESET == USART_GetFlagStatus(SPECIFIE_USARTx,USART_FLAG_TXE));
	return (int)USART_ReceiveData(SPECIFIE_USARTx);
}

/****
	* @brief	串口打印 			  
	* @param   	format  字符串，包含了要被写入到字符串 str 的文本。它可以包含嵌入的 format 标签，
    *                   format 标签可被随后的附加参数中指定的值替换，并按需求进行格式化  
	* @return   无  	
	* Sample usage: Usart_sprintf("Number=%d\r\n",125);
    */
void Usart_sprintf(char *format, ...)
{
    char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Usart_SendString(SPECIFIE_USARTx,String);
}

#ifdef RX_HEX
uint8_t Usart_GetRxFlag()
{
    if(Usart_RxFlag == 1)
    {
        Usart_RxFlag = 0 ;
        return 1;
    }
    return 0;
}

void SPECIFIE_USART_IRQHNADLER()
{
    static uint8_t RX_State = 0;
    static uint8_t RX_packet = 0;
    if( SET == USART_GetITStatus(SPECIFIE_USARTx,USART_IT_RXNE))
    {
        uint8_t RX_Data = USART_ReceiveData(SPECIFIE_USARTx);
        if(RX_State == 0)
        {
            if(RX_Data == 0xFF)
            {
                RX_State = 1;
                RX_packet = 0;
            }
        }
        else if(RX_State == 1)
        {
            Usart_RxHEX[RX_packet] = RX_Data;
            RX_packet++;
            if(RX_MAX <= RX_packet)
            {
                RX_State = 2;
            }
        }
        else if(RX_State == 2)
        {
            if(RX_Data == 0xFE)
            {
                RX_State = 0;
                Usart_RxFlag = 1 ;
            }
        }
        USART_ClearITPendingBit(SPECIFIE_USARTx,USART_IT_RXNE);
    }
}
#else //RX_CHARACTER
void SPECIFIE_USART_IRQHNADLER()
{
    static uint8_t RX_State = 0;
    static uint8_t RX_packet = 0;
    if( SET == USART_GetITStatus(SPECIFIE_USARTx,USART_IT_RXNE))
    {
        char RX_Data = USART_ReceiveData(SPECIFIE_USARTx);
        if(RX_State == 0)
        {
            if(RX_Data == '@' && Usart_RxFlag == 0)
            {
                RX_State = 1;
                RX_packet = 0;
            }
        }
        else if(RX_State == 1)
        {
            if(RX_Data == '\r')
            {
                RX_State = 2;
            }
            else 
            {
                Usart_RxCharacter[RX_packet] = RX_Data;
                RX_packet++;
            }
        }
        else if(RX_State == 2)
        {
            if(RX_Data == '\n')
            {
                RX_State = 0;
                Usart_RxCharacter[RX_packet] = '\0';
                Usart_RxFlag = 1 ;
            }
        }
        USART_ClearITPendingBit(SPECIFIE_USARTx,USART_IT_RXNE);
    }
}
#endif
