#ifndef __TIMER
#define __TIMER
#include "Include.h"

void TIM2_Timer_Init(u32 arr,u16 psc);
void TIM3_Timer_Init(u32 arr,u16 psc);
void TIM4_Timer_Init(u32 arr,u16 psc);
void TIM5_Timer_Init(u32 arr,u16 psc);

void TIMx_Timer_Init(u8 x,u32 time);

void TIM2_IRQ(void);
void TIM3_IRQ(void);
void TIM4_IRQ(void);
void TIM5_IRQ(void);


#endif

