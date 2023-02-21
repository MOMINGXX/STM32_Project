#include "ROCKER.h"

__IO uint16_t Rocker_Value_BUFF[NUMCHANNEL] = { 0 };

/****
	* @brief   摇杆 GPIO 配置			  
	* @param   无
	* @return  无    	
	* Sample usage:ROCKER_GPIO_Config(); 
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

void AD_GetValue()
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,2);//给传输计数器赋值
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); 
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//获取标志位     转运完成
	DMA_ClearFlag(DMA1_FLAG_TC1);
}

