#include "RainDrop_Module.h"

__IO uint16_t Rain_size;

/****
	* @brief    GPIO ��ʼ�� ����			  
	* @param   	��
	* @return   ��    	
	* Sample usage:RainDrop_GPIO_Config(); 
    */
static void RainDrop_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//����GPIOʱ��
	RAINDROP_APBxCLKCMD(RAINDROP_DO_CLK | RAINDROP_AO_CLK,ENABLE);
	
	//GPIO��������  DO ����
	GPIO_InitStruct.GPIO_Pin = RAINDROP_DO_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;			//����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RAINDROP_DO_GPIO_PORT,&GPIO_InitStruct);

	//GPIO��������  AO ģ������
	GPIO_InitStruct.GPIO_Pin = RAINDROP_AO_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;			//ģ������
	GPIO_Init(RAINDROP_AO_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief    ADC ��ʼ�� ���� 			  
	* @param   	��
	* @return   ��    	
	* Sample usage:RainDrop_ADC_Config(); 
    */
static void RainDrop_ADC_Config()
{
	ADC_InitTypeDef ADC_InitStruct;

	//����ADCʱ��
	RAINDROP_ADC_APBxCLKCMD(RAINDROP_ADC_CLK,ENABLE);

	//ADC��������
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//����ģ��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//���й���ת���� ADC ͨ������Ŀ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;			//��ͨ��
	ADC_Init(RAINDROP_ADCx,&ADC_InitStruct);

	//����ADCCLK��Ƶ��  6��Ƶ ADCCLK=72MHz/6=12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	

	//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(RAINDROP_ADCx,RAINDROP_ADC_Channel,1,ADC_SampleTime_55Cycles5);
	
	//ʹ��ADc
	ADC_Cmd(RAINDROP_ADCx,ENABLE);

	//ʹ��ADC_DMA
	ADC_DMACmd(RAINDROP_ADCx,ENABLE);

	//ʹ��ָ���� ADC �����ת����������
	ADC_SoftwareStartConvCmd(RAINDROP_ADCx,ENABLE);

	//У׼
	ADC_ResetCalibration(RAINDROP_ADCx);						//ADC��λУ׼
	while(ADC_GetResetCalibrationStatus(RAINDROP_ADCx));		//���ظ�λУ׼״̬
	ADC_StartCalibration(RAINDROP_ADCx);						//ADC��λУ׼
	while(ADC_GetCalibrationStatus(RAINDROP_ADCx));				//�ȴ�У׼���
}

/****
	* @brief    DMA ��ʼ�� ����	  
	* @param   	��
	* @return   ��    	
	* Sample usage:RainDrop_DMA_Config(); 
    */
static void RainDrop_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStruct;

	//����DMAʱ��
	RAINDROP_DMA_AHBxCLKCMD(RAINDROP_DMA_CLK,ENABLE);

	//DMA��������
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(RAINDROP_ADCx->DR));	//�����ַ	ADC���ݼĴ�����ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Rain_size;		//�洢����ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;					//������Ϊ���ݴ������Դ
	DMA_InitStruct.DMA_BufferSize = 1;								//DMA ����Ĵ�С
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//�����ַ�Ĵ�������
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;			//�ڴ��ַ�Ĵ�������
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //���ݿ��Ϊ 16 λ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//���ݿ��Ϊ 16 λ
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;				//�����ȼ�
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;					//������ѭ������ģʽ
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;						//���赽�洢��
	DMA_Init(RAINDROP_DMA_Channel,&DMA_InitStruct);

	//ʹ��DMA
	DMA_Cmd(RAINDROP_DMA_Channel,ENABLE);
}

/****
	* @brief    ģ�� ��ʼ�� 			  
	* @param   	��
	* @return   ��    	
	* Sample usage:RainDrop_Init(); 
    */
void RainDrop_Init()
{
	RainDrop_GPIO_Config();
	RainDrop_ADC_Config();
	RainDrop_DMA_Config();
}

/****
	* @brief    ��μ��		  
	* @param   	��
	* @return   ��    	
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