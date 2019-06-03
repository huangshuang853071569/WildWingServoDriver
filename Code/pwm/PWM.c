/**------------------------------------------------------------------**/
//* File name ：PWM.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include"PWM.h"

/**
	*@brief 	TIM3初始化
	*@param		NONE
	*@return	NONE
	*/
void TIM3_Config(void)
{
	TIM3_GPIO_Config(); //GPIO初始化
	TIM3_Mode_Config();	//模式初始化
}


/**
	*@brief 	TIM3定时器GPIO初始化：设置PWM输出的引脚
	*@param		NONE
	*@return	NONE
	*/
 void TIM3_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE); // 开GPIOA,GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 开TIM3时钟
	
	// GPIO初始化
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;     //CH1输出:PA6
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/**
	*@brief 	TIM3定时器模式初始化
	*@param 	NONE
	*@return  NONE
	*/
void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/****************时基初始化***************/
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseStructure.TIM_Period=17999;//定时器从0计数到999，即1000次为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler=80;//设置预分频：不预分频
	//TIM_TimeBaseStructure.TIM_RepetitionCounter=
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//调用初始化函数
}


/**
	*@brief 	引脚PA6输出PWM
	*@param		u16 CCR1_Val:高电平所占的数值
	*@return	NONE
	*/
 void PWM1_Out(u16 CCR1_Val)
{

	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	/****************使用TIM3_CH1配置****************/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//使能定时器输出
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//配置为PWM1模式
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val; //直译为跳变，即设置比较寄存器中的数值
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//写入结构体
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能TIM3在CCR1上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);  //使能装载寄存器
	TIM_Cmd(TIM3,ENABLE);  //使能定时器3
}
