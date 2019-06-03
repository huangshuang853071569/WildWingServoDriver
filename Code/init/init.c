/**------------------------------------------------------------------**/
//* File name ：init.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/6/3				             
//* Version   : v1.0				                     
/**------------------------------------------------------------------**/
#include "init.h"

/**
	*	@breif	device init
	* @param
	* @ruturn
	*/
void init()
{
	delay_init();																		//延时函数初始化
	
	ADC1_Config();																	//初始化ADC1，启动AD转换
	
	TIM4_Cap_Init(0xffff,72-1);											//TIM4初始化：接收机PWM输入
	
	TIM3_GPIO_Config();															//PWM输出初始化
	
	Motor_init();
	
	uart_init(115200);															//USART1初始化
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断优先级分组
}
	