/**------------------------------------------------------------------**/
//* File name ：led.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include "led.h"
	    
/**
	*@breif 	LED初始化
	*@param		NONE
	*@return 	NONE
	*/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	 //IO口速度为50MHz

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;						 	 //板载指示灯 PB11
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 			  
 GPIO_SetBits(GPIOB,GPIO_Pin_10);						 					  
	
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14;		//模式切换指示灯 PB13 PB14
 GPIO_Init(GPIOB, &GPIO_InitStructure);	
 GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14);					

}
 