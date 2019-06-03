/**------------------------------------------------------------------**/
//* File name ：ADC.h                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#ifndef ADC_H
#define ADC_H
#define	ADC1_DR_Adress	((u32)0x40012400+0x4c)	//ADC1数据寄存器的地址
#include "stm32f10x.h"

void ADC1_Config(void);									//ADC1初始化
void ADC_GPIO_Config(void);							//ADC1端口初始化
void ADC_Mode_Config(void);							//ADC模式初始化
void filter(void);											//平均数滤波
float Get_Anolog_Voltage(u16 AD_VALUE);	//将ADC采集的结果换算成实际输入的模拟电压值

#endif	/*ADC_H*/
