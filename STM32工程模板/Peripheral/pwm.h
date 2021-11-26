#ifndef __PWM
#define __PWM
//#include "Include.h"
#include "sys.h"
#define PWM_Polarity_High  1
#define PWM_Polarity_Low  0

void TIM2_PWM_Init(u32 arr,u32 psc,u8 mode);
void TIM3_PWM_Init(u32 arr,u32 psc,u8 mode);
void TIM4_PWM_Init(u32 arr,u32 psc,u8 mode);
void TIM5_PWM_Init(u32 arr,u32 psc,u8 mode);

void PWM2_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void PWM3_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void PWM4_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void PWM5_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
#endif

