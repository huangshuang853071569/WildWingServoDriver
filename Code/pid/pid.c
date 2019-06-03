/**-------------------------------------------------------------**/
/** File name : pid.c											**/
/**	Author	  :	Huangshuang										**/
/**	Data	  : 2019/5/31										**/
/**	Version	  : V1.0											**/
/**-------------------------------------------------------------**/
#include "usart.h"
#include "pid.h"

float err_ext;			//外环误差值
float obs_ext;			//外环观测值
float exc_ext;			//外环期望值
float out_ext;			//外环输出值
float obs_ext_last;		//上一次的外环观测值*

float err_ins;			//内环误差值
float obs_ins;			//内环观测值
float exc_ins;			//内环期望值
float out_ins;			//内环输出值	*
	
float integral_ins;		//内环积分值	*
float err_ins_last;		//上一次的内环误差	*



/**
  *	@brief		PID CONTROLL
  *	@param
  *	@return		pid_out :controllor output
  */
float pid_control(float except,float current,float delta_T)
{
	float pid_out;			//控制器输出值
	
	obs_ext = current;		
	exc_ext	= except;		

  /**----------------------------Extern Control----------------------------**/
	err_ext	= exc_ext - obs_ext;					//求外环误差 
	if(fabs(err_ext)<200)err_ext=0;				//死区
	out_ext = err_ext * KP_EXT;						//求外环输出
  /**----------------------------------------------------------------------**/
  
  
	exc_ins = out_ext;								//内环期望值=外环输出值
	obs_ins	= (obs_ext-obs_ext_last)/delta_T;		//内环观测值=外环观测值的微分
	
	
  /**----------------------------Inside Control----------------------------**/
	err_ins = exc_ins - obs_ins;					//求内环误差  														
	//if(fabs(err_ins)<300)err_ins=0;
	
//	if(																		//抗饱和积分
//	   ( (out_ins > PID_MAX)&&(err_ins > 0) )||( (out_ins < PID_MIN)&&(err_ins < 0) ) )	 
//	{
//		printf("here! \r\n");												
//	}
//	else 
	{integral_ins=integral_ins+err_ins;}
	
	#ifdef ENABLE_INTEGRAL_SEPARATING				//如果使能了积分分离
	{
		if(fabs(err_ins) > ERR_TRD_INS)				//误差绝对值在阈值之外，使用PD控制
		{											
			out_ins = 
			KP_INS * err_ins + 							
			0				 +							
			KD_INS * ((err_ins-err_ins_last)/delta_T);	
		}
		else										//误差绝对值小于阈值，使用PID控制
		{
			out_ins = 
			KP_INS * err_ins + 							
			KI_INS * integral_ins +						
			KD_INS * ((err_ins-err_ins_last)/delta_T);	
		}
	}
	#else
	{
		out_ins = 
			KP_INS * err_ins + 							
			KI_INS * integral_ins +						
			KD_INS * ((err_ins-err_ins_last)/delta_T);	
	}
	#endif
  /**----------------------------------------------------------------------**/
  
	err_ins_last = err_ins;							//保存本次内环误差
	obs_ext_last = obs_ext;							//保存本次外环观测值
	
	pid_out	= out_ins;
	if((pid_out<22000)&&(pid_out>1500))pid_out=16000;
	if((pid_out>-22000)&&(pid_out<-1500))pid_out=-16000;
	if(fabs(pid_out)<=1500)pid_out=0;
	return pid_out;
}
