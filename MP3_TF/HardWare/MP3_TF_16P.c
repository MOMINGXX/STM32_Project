#include "MP3_TF_16P.h"

static uint8_t Send_Buf[10] = {0} ; 

/****
	* @brief	和校验   			  
	* @param   	Str     接收的指令地址
    * @param    Len     指令长度	
	* @return   无	
	* Sample usage: DoSum(Send_buf,6);
    */
static void DoSum(uint8_t *Str,uint8_t Len)
{
    uint16_t xorsum = 0;
    uint8_t i = 0;
    for(i=0;i<Len;i++)
    {
        xorsum += Str[i];
    }
    xorsum = 0 - xorsum;
    *(Str + i) = (uint8_t)(xorsum >> 8);
    *(Str + i + 1) = (uint8_t)(xorsum & 0x00ff);
}

/****
	* @brief	发送指令			
	* @param    Len     指令长度	
	* @return   无	
	* Sample usage: Send_Cmd(6);
    */
static void Send_Cmd(uint8_t Len)
{
    uint8_t i = 0;
    Usart_SendByte(SPECIFIE_USARTx,0x7E);        //起始
    for(i=0;i<Len;i++)
    {
        Usart_SendByte(SPECIFIE_USARTx,Send_Buf[i]);     //数据
    }
    Usart_SendByte(SPECIFIE_USARTx,0xEF);        //结束
}

/****
	* @brief	对模块发送指令	
    * @param    CMD         控制指令    播放 暂停...
    * @param 	feedback	命令反馈    0x00 不反馈  0x01 反馈
	* @param    dat         指定歌曲	0 ~ 0xffff
    * @return   无	
	* Sample usage: Uart_SendCMD(Specify_Music ,0x00,36);
    */
void Uart_SendCMD(uint8_t CMD ,uint8_t feedback ,uint16_t dat)
{
    Send_Buf[0] = 0xff; //保留字节 
    Send_Buf[1] = 0x06; //长度
    Send_Buf[2] = CMD; //控制指令
    Send_Buf[3] = feedback;//是否需要反馈
    Send_Buf[4] = (uint8_t)(dat >> 8);//datah 
    Send_Buf[5] = (uint8_t)(dat); //datal 
    DoSum(&Send_Buf[0],6); //校验
    Send_Cmd(8); 
}

/****
	* @brief	播放指定文件夹指定歌曲 
    * @param    CMD         控制指令    播放 暂停...
    * @param 	feedback	命令反馈    0x00 不反馈  0x01 反馈
    * @param    Folder		指定文件夹  0-99
	* @param    dat         指定歌曲	0 ~ 0xff
    * @return   无	
	* Sample usage:Uart_SendFolder(Specify_Folder,0x00,2,6);
    */
void Uart_SendFolder(uint8_t CMD,uint8_t feedback,uint8_t Folder,uint8_t dat) 
{
	Send_Buf[0] = 0xff; //保留字节 
	Send_Buf[1] = 0x06; //长度
	Send_Buf[2] = CMD; //控制指令
	Send_Buf[3] = feedback;//是否需要反馈
	Send_Buf[4] = (uint8_t)(Folder);
	Send_Buf[5] = (uint8_t)(dat); 
	DoSum(&Send_Buf[0],6); //校验
	Send_Cmd(8);  //发送此帧数据
}
