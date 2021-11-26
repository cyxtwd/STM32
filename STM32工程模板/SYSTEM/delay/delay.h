#ifndef __DELAY_H
#define __DELAY_H 
  
#include "Include.h"  



void SysTick_ConfigInit(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);
void delay_xms(u32 nms);
void SysTick_Handler(void);
u32 getSysTickCnt(void);


#endif





























