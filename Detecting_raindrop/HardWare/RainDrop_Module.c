#include "RainDrop_Module.h"

__IO uint16_t Rain_size;

/****
	* @brief    GPIO 初始化 配置			  
	* @param   	无
	* @return   无    	
	* Sample usage:RainDrop_GPIO_Config(); 
    */
static void RainDrop_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开启GPIO时钟
	RAINDROP_APBxCLKCMD(RAINDROP_DO_CLK | RAINDROP_AO_CLK,ENABLE);
	
	//GPIO参数配置  DO 上拉
	GPIO_InitStruct.GPIO_Pin = RAINDROP_DO_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;			//上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RAINDROP_DO_GPIO_PORT,&GPIO_InitStruct);

	//GPIO参数配置  AO 模拟输入
	GPIO_InitStruct.GPIO_Pin = RAINDROP_AO_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	GPIO_Init(RAINDROP_AO_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief    ADC 初始化 配置 			  
	* @param   	无
	* @return   无    	
	* Sample usage:RainDrop_ADC_Config(); 
    */
static void RainDrop_ADC_Config()
{
	ADC_InitTypeDef ADC_InitStruct;

	//开启ADC时钟
	RAINDROP_ADC_APBxCLKCMD(RAINDROP_ADC_CLK,ENABLE);

	//ADC参数配置
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//连续模拟
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//进行规则转换的 ADC 通道的数目
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;			//单通道
	ADC_Init(RAINDROP_ADCx,&ADC_InitStruct);

	//配置ADCCLK分频器  6分频 ADCCLK=72MHz/6=12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	

	//设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
	ADC_RegularChannelConfig(RAINDROP_ADCx,RAINDROP_ADC_Channel,1,ADC_SampleTime_55Cycles5);
	
	//使能ADc
	ADC_Cmd(RAINDROP_ADCx,ENABLE);

	//使能ADC_DMA
	ADC_DMACmd(RAINDROP_ADCx,ENABLE);

	//使能指定的 ADC 的软件转换启动功能
	ADC_SoftwareStartConvCmd(RAINDROP_ADCx,ENABLE);

	//校准
	ADC_ResetCalibration(RAINDROP_ADCx);						//ADC复位校准
	while(ADC_GetResetCalibrationStatus(RAINDROP_ADCx));		//返回复位校准状态
	ADC_StartCalibration(RAINDROP_ADCx);						//ADC复位校准
	while(ADC_GetCalibrationStatus(RAINDROP_ADCx));				//等待校准完毕
}

/****
	* @brief    DMA 初始化 配置	  
	* @param   	无
	* @return   无    	
	* Sample usage:RainDrop_DMA_Config(); 
    */
static void RainDrop_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStruct;

	//开启DMA时钟
	RAINDROP_DMA_AHBxCLKCMD(RAINDROP_DMA_CLK,ENABLE);

	//DMA参数配置
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(RAINDROP_ADCx->DR));	//外设地址	ADC数据寄存器地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Rain_size;		//存储器地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;					//外设作为数据传输的来源
	DMA_InitStruct.DMA_BufferSize = 1;								//DMA 缓存的大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址寄存器不变
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;			//内存地址寄存器不变
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //数据宽度为 16 位
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//数据宽度为 16 位
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;				//中优先级
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;					//工作在循环缓存模式
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;						//外设到存储器
	DMA_Init(RAINDROP_DMA_Channel,&DMA_InitStruct);

	//使能DMA
	DMA_Cmd(RAINDROP_DMA_Channel,ENABLE);
}

/****
	* @brief    模块 初始化 			  
	* @param   	无
	* @return   无    	
	* Sample usage:RainDrop_Init(); 
    */
void RainDrop_Init()
{
	RainDrop_GPIO_Config();
	RainDrop_ADC_Config();
	RainDrop_DMA_Config();
}

/****
	* @brief    雨滴检测		  
	* @param   	无
	* @return   无    	
	* Sample usage:RainDrop_Detect(); 
    */
void RainDrop_Detect()
{
	if(RESET == GPIO_ReadInputDataBit(RAINDROP_DO_GPIO_PORT,RAINDROP_DO_GPIO_PIN))
	{
		Led_On(LED_GPIO_PORT,LED_GPIO_PIN);		
	}
	else Led_Off(LED_GPIO_PORT,LED_GPIO_PIN);
}