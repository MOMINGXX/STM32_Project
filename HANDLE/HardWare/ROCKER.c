#include "ROCKER.h"

uint16_t Rocker_Value_BUFF[NUMCHANNEL] = { 0 };
uint8_t L_DIR,R_DIR;

/****
		* @brief   摇杆 GPIO 配置			  
		* @param   无
		* @return  无    	
		* Sample usage:ROCKER_GPIO_Config(); 
		* note
    */
static void ROCKER_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //开启GPIO时钟
    ROCKER_ADCLx_GPIO_APBxClockCMD(ROCKER_ADCLx_GPIO_CLK | ROCKER_ADCRx_GPIO_CLK,ENABLE);

    //GPIO参数 配置
    GPIO_InitStruct.GPIO_Pin = ROCKER_ADCL1x_GPIO_PIN | ROCKER_ADCL2x_GPIO_PIN | ROCKER_ADCR3x_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  			//模拟输入
    GPIO_Init(ROCKER_ADCLx_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = ROCKER_ADCR1x_GPIO_PIN | ROCKER_ADCR2x_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  			//模拟输入
    GPIO_Init(ROCKER_ADCRx_GPIO_PORT,&GPIO_InitStruct);
}

/*DMA参数
typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;      //外设地址
  uint32_t DMA_MemoryBaseAddr;          //存储器地址
  uint32_t DMA_DIR;                     //传输方向
  uint32_t DMA_BufferSize;              //传输数目
  uint32_t DMA_PeripheralInc;           //外设地址增量模式
  uint32_t DMA_MemoryInc;               //存储器地址增量模式     
  uint32_t DMA_PeripheralDataSize;      //外设数据宽度
  uint32_t DMA_MemoryDataSize;          //存储器数据宽度
  uint32_t DMA_Mode;                    //模式选择
  uint32_t DMA_Priority;                //通道优先级
  uint32_t DMA_M2M;                     //存储器到存储器模式
}DMA_InitTypeDef;
*/

/****
	* @brief    摇杆 DMA 配置 			  
	* @param   	无
	* @return   无    	
	* Sample usage:ROCKER_DMA_Config(); 
    */
static void ROCKER_DMA_Config()
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_DeInit(ROCKER_DMAX_Channel);
    //开启DMA时钟
    ROCKER_DMAx_APBxClockCMD(ROCKER_DMAx_CLK,ENABLE);
    //参数配置
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(ROCKER_ADCx->DR));     //外设地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Rocker_Value_BUFF;            //存储器地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                 //外设作为数据传输的来源          
	DMA_InitStruct.DMA_BufferSize = NUMCHANNEL;                     //传输数目
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //外设地址寄存器不变      
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;            //内存地址寄存器递增          
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //数据宽度为 16 位 
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            //数据宽度为 16 位    
	DMA_InitStruct.DMA_Mode =  DMA_Mode_Circular;           //循环缓存模式               
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;      	//高优先级          
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;               //外设到内存;   
    DMA_Init(ROCKER_DMAX_Channel,&DMA_InitStruct);

    //开启DMA
    DMA_Cmd(ROCKER_DMAX_Channel,ENABLE);
}

/****
	* @brief    ADC 配置 			  
	* @param   	无
	* @return   无    	
	* Sample usage:ROCKER_ADCx_Config(); 
    */
static void ROCKER_ADCx_Config()
{
    ADC_InitTypeDef ADC_InitStruct;
    //开启ADC时钟
    ROCKER_ADCx_APBxClockCMD(ROCKER_ADCx_CLK,ENABLE);
    //参数配置
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;         //连续转换;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //右对齐
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   //转换由软件而不是外部触发启动
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //独立模式
    ADC_InitStruct.ADC_NbrOfChannel = NUMCHANNEL;           //进行规则转换的 ADC 通道的数目
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;               //多通道
    ADC_Init(ROCKER_ADCx,&ADC_InitStruct);

    //设置 ADC 时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);       //8分频 ADCCLK=72MHz/8=9MHz     108MHz/8 = 13

    //设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel1,1,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel2,2,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel3,3,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel4,4,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel5,5,ADC_SampleTime_239Cycles5);

    //使能ADC_DMA
    ADC_DMACmd(ROCKER_ADCx,ENABLE);

    //开启ADC
    ADC_Cmd(ROCKER_ADCx,ENABLE);
    Delay_us(30);

    //校准
    ADC_ResetCalibration(ROCKER_ADCx);                  //ADC复位校准
    while(ADC_GetResetCalibrationStatus(ROCKER_ADCx));  //等待复位校准完成
    ADC_StartCalibration(ROCKER_ADCx);                  //ADC开始校准  
    while(ADC_GetCalibrationStatus(ROCKER_ADCx));       //等待校准完成

    //使能指定的 ADC 的软件转换启动功能
    ADC_SoftwareStartConvCmd(ROCKER_ADCx,ENABLE);
}

/****
	* @brief    ADC 初始化		  
	* @param   	无
	* @return   无    	
	* Sample usage:ROCKER_ADCx_Config(); 
    */
void ROCKER_Init()
{
    ROCKER_GPIO_Config();
	ROCKER_DMA_Config();
	ROCKER_ADCx_Config(); 
}

/****
	* @brief    ADC 数据处理		  
	* @param   	Value   处理的数据
	* @return   无    	
	* Sample usage:ROCKER_COORDINATE(&Value);
    */
void ROCKER_COORDINATE(ROCKER_Value *Value)
{
    Value->ROCKER_RY_Value =    (Rocker_Value_BUFF[2] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_RX_Value =    (Rocker_Value_BUFF[3] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_LY_Value =    (Rocker_Value_BUFF[0] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_LX_Value =    (Rocker_Value_BUFF[1] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;  

    float voltage = (float)(Rocker_Value_BUFF[4] * 3.3 / ADC_RESOLUTION);       // 计算电压值
    Value->Electricity = voltage * 3 / BATTERY_RATED_VOLTAGE*100;             //计算电量  电阻(R21(R1+R2))1/3分压                                                          
}

void ROCKER_Driction()
{
    ROCKER_Value Value;
    ROCKER_COORDINATE(&Value);
    if(0 <= Value.ROCKER_RX_Value && Value.ROCKER_RX_Value <= 25) R_DIR = 0;    //右摇杆右
    if(75 <= Value.ROCKER_RX_Value && Value.ROCKER_RX_Value < 100) R_DIR = 1;   //右摇杆左
    if(0 <= Value.ROCKER_RY_Value && Value.ROCKER_RY_Value <= 25) R_DIR = 2;    //右摇杆s
    if(75 <= Value.ROCKER_RY_Value && Value.ROCKER_RY_Value < 100) R_DIR = 3;    //右摇杆x
    if(25 < Value.ROCKER_RY_Value && Value.ROCKER_RY_Value < 75) R_DIR = 4;      //右摇杆中间

    if(0 <= Value.ROCKER_LX_Value && Value.ROCKER_LX_Value <= 25) L_DIR = 0;    //左摇杆右
    if(75 <= Value.ROCKER_LX_Value && Value.ROCKER_LX_Value < 100) L_DIR = 1;   //左摇杆左
    if(0 <= Value.ROCKER_LY_Value && Value.ROCKER_LY_Value <= 25) L_DIR = 2;    //左摇杆s
    if(75 <= Value.ROCKER_LY_Value && Value.ROCKER_LY_Value < 100) L_DIR = 3;   //左摇杆x
    if(25 < Value.ROCKER_LY_Value && Value.ROCKER_LY_Value < 75) L_DIR = 4;      //左摇杆中间
}

/****
	* @brief    ADC 数据发送	  
	* @param   	无
	* @return   无    	
	* Sample usage:ROCKER_DirSend(); 
    */
void ROCKERData_Send()
{
    uint8_t ROCKER_Buff[12] = "0";
    ROCKER_Value Value;
    ROCKER_COORDINATE(&Value);
    ROCKER_Buff[0] = 'R';
    ROCKER_Buff[1] = 'Y';
    ROCKER_Buff[2] = Value.ROCKER_RY_Value;
    ROCKER_Buff[3] = 'X';
    ROCKER_Buff[4] = Value.ROCKER_RX_Value;
    ROCKER_Buff[5] = 'L';
    ROCKER_Buff[6] = 'Y';
    ROCKER_Buff[7] = Value.ROCKER_LY_Value;
    ROCKER_Buff[8] = 'X';
    ROCKER_Buff[9] = Value.ROCKER_LX_Value;
    ROCKER_Buff[10] = '0';
    NRF24L01_TX_Mode();
	if(NRF24L01_TxPacket(ROCKER_Buff) == NRF24L01_TX_DS)
	{
		LED1_TOGGLE;
	}
	else
	{										   	
 		printf("ROCKER Send failed !\n");	
	}
}

