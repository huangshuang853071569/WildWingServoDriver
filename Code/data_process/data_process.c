/**----------------------------------------------------------**/
//*	File name : data_process.c									 
//*	Author	  : Huangshuang 								 
//*	Data 	    : 2019/5/31									 
//*	Vertion	  : V1.0										 
/**----------------------------------------------------------**/
#include "data_process.h"

float Anolog_Voltage_1;												    //采样得到的电压
extern vu16 After_filter[];  											//平均数滤波后的最终数据
extern  u32 pwm_in_ch1;														//输入的PWM脉宽

volatile float except_pos;																//期望位置 0~33000
volatile float current_pos;																//当前位置 0~33000
volatile float PID_Control_Out;														//PID控制后的输出值										

/**
	*	@breif 输入PWM值映射为期望位置	
	* @param pwm_in:PWM输入脉宽
	* @return 期望位置
	*/
float get_except_pos(float pwm_in)
{
	if(pwm_in<1000)pwm_in=1000;
	if(pwm_in>2000)pwm_in=2000;
	return ((float)(33*pwm_in-49500));					//从1000~2000映射为-16500~16500
}
							
/**
	*	@breif 输入PWM值映射为期望位置	
	* @param float vol : 电压
	* @return 期望位置
	*/
float get_current_pos(void)
{
	filter();	//均值滤波																			
	Anolog_Voltage_1=Get_Anolog_Voltage(After_filter[0]); 	//读取ADC电压	
	return Anolog_Voltage_1*10000-16500; 										//计算当前位置	//从0~3.3映射为-16500~16500
}

/**
	*	@breif data_process	
	* @param float vol : 电压
	* @return 期望位置
	*/
void data_process(void)
{
	except_pos=get_except_pos((float)pwm_in_ch1);	//获取期望位置
	current_pos=get_current_pos();								//获取当前位置
}
	