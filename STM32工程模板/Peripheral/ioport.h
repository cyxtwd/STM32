#ifndef __io
#define __io 
//#include "Include.h"
#include "sys.h" 
#include "stm32f4xx.h" 

#define LED_Red PAout(3)
#define LED_Grn PAout(4)

#define RGB_Red PBout(0)
#define RGB_Grn PCout(5)
#define RGB_Blu PCout(4)

#define LED_ON  0
#define LED_OFF 1

void LED_Init(void);
void RGB_LED_Init(void);
void BEEP_Init(void);
void KEY_Init(void);
void our_Init(void);

#define BEEP PAout(15)
#define BEEP_ON 1
#define BEEP_OFF 0

#define KEY1 PAin(6)
#define KEY2 PAin(5)

#define long_timer 100
#define double_timer 10¡¢

#endif

