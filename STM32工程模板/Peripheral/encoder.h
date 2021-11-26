#ifndef __encoder__
#define __encoder__

//#include "Include.h"
#include "sys.h"
#include <stdint.h>
void encoder_tim_init(void);
float Read_Velocity(void);

void encoder_tim_init1(void);
float Read_Velocity1(void);
#define encoder_tim                                  TIM4
#define RCC_APB1Periph_encoder        RCC_APB1Periph_TIM4
#define RCC_AHB1Periph_GPIO_encoder  RCC_AHB1Periph_GPIOD
#define GPIO_encoder                                GPIOD
#define GPIO_PinSourceA                  GPIO_PinSource12
#define GPIO_PinSourceB                  GPIO_PinSource13
#define GPIO_AF_encoder                      GPIO_AF_TIM4


#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。

#endif 
