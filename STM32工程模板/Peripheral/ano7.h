#ifndef __ano__
#define __ano__

//#include "Include.h"
#include "sys.h"
#include "usart.h"
#include <string.h>
#include "stdlib.h"
void UART1_Send_Str(u8 *s,u8 cnt);
void Test_Send_User(int16_t data1, int16_t data2, int16_t data3);


#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

#endif

