/**------------------------------------------------------------------**/
//* File name ： main.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#include "include.h"

extern float except_pos;			//期望位置
extern float current_pos;			//当前位置
extern float PID_Contol_Out;	//pid控制器的最后输出值
extern float integral_ins;		//积分数值

extern float PID_Control_Out;	//pid控制后的输出值
int main(void)
{
	init();						//硬件初始化
	
	while(1)
	{
		data_process();	//输入数据处理
		
			
		PID_Control_Out=pid_control(except_pos,current_pos,5);
		
		Motor_Control();			//PID控制

		delay_ms(1);

	}		
}

/***相关数据打印***/
/*
	printf("%f \r\n",except_pos);												//期望位置
	printf("%f \r\n",integral_ins);											//积分数值
	printf("%f \r\n",current_pos);											//当前位置
	printf("err = %f \r\n",except_pos-current_pos);			//误差
	printf("%f \r\n",PID_Contol_Out);										//PID最后输出值
*/
