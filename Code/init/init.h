/**------------------------------------------------------------------**/
//* File name £ºinit.h                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#ifndef _INIT_H
#define _INIT_H

#include "stm32f10x.h"
#include "led.h"
#include "ADC.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "receiver.h"
#include "PWM.h"

void Motor_init(void);
void init();

#endif
