/**------------------------------------------------------------------**/
//* File name £ºPWM.h                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#ifndef _PWM_OUT_H
#define _PWM_OUT_H

#include"stm32f10x.h"

 void TIM3_GPIO_Config(void);
 void TIM3_Mode_Config(void);
 void TIM3_Config(void);
 void PWM1_Out(u16 CCR1_Val);
 
#endif
