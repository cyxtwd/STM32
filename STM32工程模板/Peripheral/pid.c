#include "pid.h"

/**************************************************************************
�������ܣ�����PI������
��� ֵ������������ֵ��Ŀ���ٶ�
���� ֵ�����PWM
���ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int Encoder,_pid_Data Target)
{ 	
	 
	 Target.Bias=Target.Value-Encoder;                                  //����ƫ��
	 Target.Pwm+=Target.Kp*(Target.Bias-Target.Last_bias)+Target.Ki*Target.Bias;   //����ʽPI������
	 Target.Last_bias=Target.Bias;	                                   //������һ��ƫ�� 
	if(Target.Pwm >= Target.Pwm_max )                                       //�޷�
		Target.Pwm = Target.Pwm_max;                                         //1000�Ǹ���pwm����
	if(Target.Pwm <= -Target.Pwm_max )
		Target.Pwm = -Target.Pwm_max;
	 return Target.Pwm;                                           //�������
}
////////////////////////////////////////////////////////////////////////////
/***************************************************************************
* 									pid��ز�����ʼ��
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
