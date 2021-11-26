#ifndef __pid
#define __pid

//#include "Include.h"
#include "pid.h"
#include "encoder.h"
#include "pwm.h"
#include "stm32f4xx.h" 
#include "stm32f4xx_gpio.h"


typedef struct 
{
    float Value;  //�����ٶ�
    float Bias;	//���
    float Pwm;  	//���ֵ
    float Last_bias;  //��һ�ε����
    float Kp;			//
    float Ki;			//
    float Kd;			//
	 int Pwm_max;		//�޷�
}_pid_Data;
extern _pid_Data pid;

void Coefficient_Init(void);
int Incremental_PI (int Encoder,_pid_Data Target);



#endif
