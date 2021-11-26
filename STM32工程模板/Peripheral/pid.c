#include "pid.h"

/**************************************************************************
函数功能：增量PI控制器
入口 值：编码器测量值，目标速度
返回 值：电机PWM
在速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int Encoder,_pid_Data Target)
{ 	
	 
	 Target.Bias=Target.Value-Encoder;                                  //计算偏差
	 Target.Pwm+=Target.Kp*(Target.Bias-Target.Last_bias)+Target.Ki*Target.Bias;   //增量式PI控制器
	 Target.Last_bias=Target.Bias;	                                   //保存上一次偏差 
	if(Target.Pwm >= Target.Pwm_max )                                       //限幅
		Target.Pwm = Target.Pwm_max;                                         //1000是根据pwm周期
	if(Target.Pwm <= -Target.Pwm_max )
		Target.Pwm = -Target.Pwm_max;
	 return Target.Pwm;                                           //增量输出
}
////////////////////////////////////////////////////////////////////////////
/***************************************************************************
* 									pid相关参数初始化
***************************************************************************/
_pid_Data pid;
void Coefficient_Init(){
	pid.Bias = 0;
	pid.Last_bias = 0;
	pid.Value = 1000;
	pid.Kp = 1;
	pid.Ki = 0.3;
	pid.Kd = 0;
	pid.Pwm_max = 1000;
}
