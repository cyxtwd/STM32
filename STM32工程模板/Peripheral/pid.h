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
    float Value;  //期望速度
    float Bias;	//误差
    float Pwm;  	//输出值
    float Last_bias;  //上一次的误差
    float Kp;			//
    float Ki;			//
    float Kd;			//
	 int Pwm_max;		//限幅
}_pid_Data;
extern _pid_Data pid;

void Coefficient_Init(void);
int Incremental_PI (int Encoder,_pid_Data Target);



#endif
