/**------------------------------------------------------------------**/
//* File name ：Motor.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/6/3				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include "motor.h"

extern float except_pos;																	//期望位置 0~33000
extern float current_pos;																//当前位置 0~33000
extern float PID_Control_Out;

void Motor_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);	//置0

}

/**
	*	@breif Control	
	* @param 
	* @return PID_Contol_Out PID控制器的输出
	*/
void Motor_Control(void)
{
	
	if(PID_Control_Out>0)
	{
		Roll_N	//正转
		PWM1_Out((u16)PID_Control_Out);
	}
	else if(PID_Control_Out==0)
	{
		PWM1_Out(0);
		ROLL_STOP	//停止
	}
	else
	{
		PWM1_Out((u16)(-1*PID_Control_Out));
		Roll_R	//反转
	}
}
