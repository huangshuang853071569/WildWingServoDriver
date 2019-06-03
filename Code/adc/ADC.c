/**------------------------------------------------------------------**/
//* File name ：ADC.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#include	"ADC.h"
#include	"led.h"
#include	"stm32f10x.h"

#define N 30  //每个通道采样50次
#define M 9 	//ADC用到的通道数

volatile vu16 AD_Value[N][M]; 	 //用来存放ADC的转换结果，也是内存的基地址
volatile vu16 After_filter[M];  //平均数滤波后的最终数据	

 
 /**
	* @brief ：  初始化ADC1为DMA方式，并开始AD转换,
               转换后的值ADC_ConvertedValue通过DMA传输到SRAM
	* @param ：  无
	* @retval :  无
*/
void ADC1_Config(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
}

/**
	*	@brief  :  ADC的GPIO初始化
	*	@param  :  无
	*	@retval	:	 无
*/
void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);		//使能GPIOA、GPIOB时钟
	//PA1
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruction.GPIO_Pin=GPIO_Pin_1; 
	GPIO_Init(GPIOA, &GPIO_InitStruction);

	}

/**
	* @brief  :  ADC1的模式初始化
	*	@param  :  无
	* @retval :  无
*/
void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);									//使能ADC1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);										//使能DMA1时钟
	
	//ADC1模式初始化
	ADC_DeInit(ADC1); 																										//先将ADC模式初始为缺省值
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;														//采集多个通道时，必须开启扫描模式
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;											//工作在独立ADC模式
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;											//使能连续工作模式
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;									//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;			//不使用外部中断作为ADC的触发方式
	ADC_InitStructure.ADC_NbrOfChannel=M;																	//使用9个通道
	ADC_Init(ADC1, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);																			//配置ADC时钟为PCLK2的8分频
	
	//配置ADC1的通道采样序列，且为55.5个采样周期
	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
		
	ADC_DMACmd(ADC1,ENABLE);												//使能ADC DMA	
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);				//使能ADC1中断
	ADC_Cmd(ADC1,ENABLE);														//使能ADC
	
	//ADC1校准
	ADC_ResetCalibration(ADC1);											//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));			//等待寄存器复位
	ADC_StartCalibration(ADC1);											//开始校准
	while(ADC_GetCalibrationStatus(ADC1));					//等待校准完成
	
	/*****以下是DMA1通道1配置部分*****/
	DMA_DeInit(DMA1_Channel1);																									//先将DMA1的模式恢复缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)0x40012400+0x4c;//(u32)&ADC1->DR;										//外设的地址：ADC1的数据寄存器(u32)0x40012400+0x4c (u32)&ADC1->DR
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&AD_Value;												//内存的基地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;														//DMA传输源为外设
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable ;											//内存地址需要自增
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;							//外设地址始终为ADC的数据寄存器地址，不自增
	DMA_InitStructure.DMA_BufferSize=N*M;																				//一次传输数据量的大小（DMA通道的DMA缓存大小）
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 					//内存数据宽度：半字：16位
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;		//外设数据宽度：半字：16位
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;																//循环传输
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;														//优先权：高。只使用一个DMA通道时没有区别
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;																	//禁用内存到内存的传输
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);	
	
	DMA_Cmd(DMA1_Channel1, ENABLE);								//使能DMA1通道1
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				//软件触发ADC1开始转换
	
}

/**
	*@brief : 平均值滤波
	*@param : 无
	*
**/
void filter(void)
{
	int sum=0;
	int i=0;
	u8 count=0;
	for(i=0;i<M;i++)
	{
		for(count=0;count<N;count++) sum+=AD_Value[count][i];
		After_filter[i]=sum/N;
		sum=0;
	}
}

/**
	*@brief : 换算成模拟电压值
	*@param : AD转换得到的数据
	*@return: 实际输入的模拟电压值
**/
float Get_Anolog_Voltage(u16 AD_VALUE)
{
	return AD_VALUE*3.3/4096;
}

///**
//	*@brief	:	ADC1中断函数
//	*@param	:	无
//	*
//**/
//void ADC1_2_IRQHandler(void)
//{
//	if(ADC_GetITStatus(ADC1, ADC_IT_EOC)!=RESET)
//	{
//		LED2(ON)
//	}
//}
