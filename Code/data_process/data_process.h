/**----------------------------------------------------------**/
//*	File name : data_process.h									 
//*	Author	  : Huangshuang 								 
//*	Data 	  	: 2019/5/31									 
//*	Vertion	  : v1.0										 
//*----------------------------------------------------------**/
#ifndef _DATA_PROCESS_H
#define _DATA_PROCESS_H

#include "stm32f10x.h"
#include "ADC.h"
#include "receiver.h"
#include "pid.h"
#include "PWM.h"
#include "init.h"

float get_except_pos(float pwm_in);
float get_current_pos(void);
void data_process();

#endif
