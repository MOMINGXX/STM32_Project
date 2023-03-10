#include "KEY.h"

uint8_t KeyNumber;

/****
	* @brief    KEY 引脚 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:KEY_Config(); 
    */
static void KEY_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //开启GPIO时钟
	KEY_APBx_ClockCMD(KEYx_CLK,ENABLE);
    //参数配置
    GPIO_InitStruct.GPIO_Pin =  KEY2_GPIO_PIN | KEY3_GPIO_PIN | KEY5_GPIO_PIN | KEY6_GPIO_PIN |
                                KEY7_GPIO_PIN | KEY8_GPIO_PIN | KEY10_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1x_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY4_GPIO_PIN | KEY9_GPIO_PIN | KEY11_GPIO_PIN;
    GPIO_Init(KEY2x_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN ;
    GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief    KEY 初始化			  
	* @param   	无
	* @return   无    	
	* Sample usage:KEY_Init(); 
    */
void KEY_Init()
{
    TIMEx_Init();
    KEY_Config();
}

/****
	* @brief    返回按键号		  
	* @param   	无
	* @return   Temp   按键号 	
	* Sample usage:KEY_GetNumber(); 
    */
uint8_t KEY_GetNumber()
{
    uint8_t Temp = 0;
    Temp = KeyNumber;
    KeyNumber = 0;
    return Temp;
}


/****
	* @brief    读取按键状态			  
	* @param   	无
	* @return   Number  返回按键状态    	
	* Sample usage:KEY_ReadNumber(); 
    */
static uint8_t KEY_ReadNumber()
{
    uint8_t Number = 0;
    if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == RESET) {Number = 1;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY2_GPIO_PIN) == RESET) {Number = 2;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY3_GPIO_PIN) == RESET) {Number = 3;}
    else if(GPIO_ReadInputDataBit(KEY2x_GPIO_PORT,KEY4_GPIO_PIN) == RESET) {Number = 4;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY5_GPIO_PIN) == RESET) {Number = 5;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY6_GPIO_PIN) == RESET) {Number = 6;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY7_GPIO_PIN) == RESET) {Number = 7;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY8_GPIO_PIN) == RESET) {Number = 8;}
    else if(GPIO_ReadInputDataBit(KEY2x_GPIO_PORT,KEY9_GPIO_PIN) == RESET) {Number = 9;}
    else if(GPIO_ReadInputDataBit(KEY1x_GPIO_PORT,KEY10_GPIO_PIN) == RESET) {Number = 10;}
    else if(GPIO_ReadInputDataBit(KEY2x_GPIO_PORT,KEY11_GPIO_PIN) == RESET) {Number = 11;}
    return Number;
}

/****
	* @brief    定时器扫描			  
	* @param   	无
	* @return   无   	
	* Sample usage:KEY_LOOP(); 
    */
void KEY_LOOP()
{
    uint8_t NowState,LastState;
    LastState = NowState;
    NowState = KEY_ReadNumber();
    if(LastState == 0  && NowState == 1)	{KeyNumber = 1;}
	else if(LastState == 0 && NowState == 2 )	{KeyNumber = 2;}
	else if(LastState == 0 && NowState == 3 )	{KeyNumber = 3;}
	else if(LastState == 0 && NowState == 4 )	{KeyNumber = 4;}
	else if(LastState == 0 && NowState == 5 )	{KeyNumber = 5;}
	else if(LastState == 0 && NowState == 6 )	{KeyNumber = 6;}
	else if(LastState == 0 && NowState == 7 )	{KeyNumber = 7;}
	else if(LastState == 0 && NowState == 8 )	{KeyNumber = 8;}
    else if(LastState == 0 && NowState == 9 )	{KeyNumber = 9;}
    else if(LastState == 0 && NowState == 10)	{KeyNumber = 10;}
    else if(LastState == 0 && NowState == 11)	{KeyNumber = 11;}
}

/****
	* @brief    定时器 中断函数		  
	* @param   	无
	* @return   无    	
    */
void TIMEx_IRQHandler()
{
    static uint8_t Count = 0;
    if(SET == TIM_GetITStatus(TIM2,TIM_IT_Update))
    {
        Count ++;
        if(Count >= 20)
        {
			Count = 0;
            KEY_LOOP();
        }
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}

/****
	* @brief    读取按键状态	延时函数消抖		  
	* @param   	无
	* @return   Number  返回按键状态    	
	* Sample usage:KEY_ReadNumber(); 
    */
static uint8_t Key_ReadNumber(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
    uint8_t Number = 0;
    if(RESET == GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
    {
        Delay_ms(20);
        if(RESET == GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
        {
            Delay_ms(20);
            Number = 1;
        }while(!GPIO_ReadInputDataBit(GPIOx,GPIO_Pin));
    }
    return Number;
}

/****
	* @brief    读取按键			  
	* @param   	无
	* @return   Number  返回按键   	
	* Sample usage:Key_ReadNumber(); 
    */
uint8_t Key_GetNumber()
{
    uint8_t Number = 0;
    if(Key_ReadNumber(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == SET) {Number = 1;}  
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY2_GPIO_PIN) == SET) {Number = 2;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY3_GPIO_PIN) == SET) {Number = 3;}
    else if(Key_ReadNumber(KEY2x_GPIO_PORT,KEY4_GPIO_PIN) == SET) {Number = 4;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY5_GPIO_PIN) == SET) {Number = 5;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY6_GPIO_PIN) == SET) {Number = 6;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY7_GPIO_PIN) == SET) {Number = 7;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY8_GPIO_PIN) == SET) {Number = 8;}
    else if(Key_ReadNumber(KEY2x_GPIO_PORT,KEY9_GPIO_PIN) == SET) {Number = 9;}
    else if(Key_ReadNumber(KEY1x_GPIO_PORT,KEY10_GPIO_PIN) == SET) {Number = 10;}
    else if(Key_ReadNumber(KEY2x_GPIO_PORT,KEY11_GPIO_PIN) == SET) {Number = 11;}
    return Number;
}

void Key_Send(uint8_t KetNum)
{
    uint8_t KEY_BUFF[16] = " 0 ";
	KEY_BUFF[0] = 'K';
	KEY_BUFF[1] = 'Y';
    if(KetNum)
    {
        if(1 == KetNum) { KEY_BUFF[2] = 1;}
        else if(2 == KetNum) { KEY_BUFF[3] = 2;}
        else if(3 == KetNum) { KEY_BUFF[4] = 3;}
        else if(4 == KetNum) { KEY_BUFF[5] = 4;}
        else if(5 == KetNum) { KEY_BUFF[6] = 5;}
        else if(6 == KetNum) { KEY_BUFF[7] = 6;}
        else if(7 == KetNum) { KEY_BUFF[8] = 7;}
        else if(8 == KetNum) { KEY_BUFF[9] = 8;}
        else if(9 == KetNum) { KEY_BUFF[10] = 9;}
        else if(10 == KetNum) { KEY_BUFF[11] = 10;}
        else if(11 == KetNum) { KEY_BUFF[12] = 11;}
    }
    KEY_BUFF[15] = '0';
    NRF24L01_TX_Mode();
	if(NRF24L01_TxPacket(KEY_BUFF) == NRF24L01_TX_DS)
	{
		LED1_TOGGLE;
	}
	else
	{										   	
  		printf("ROCKER Send failed !\n");	 
	}
}
