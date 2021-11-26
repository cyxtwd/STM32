#ifndef __My_USART_H_
#define __My_USART_H_

#include "Include.h"

void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);
void UART4_Init (u32 bound);
void UART5_Init (u32 bound);

void USART1_IRQ(void);
void USART2_IRQ(void);
void USART3_IRQ(void);
void UART4_IRQ (void);
void UART5_IRQ (void);

void USART1_Send(unsigned char *DataToSend ,u8 data_num);
void USART2_Send(unsigned char *DataToSend ,u8 data_num);
void USART3_Send(unsigned char *DataToSend ,u8 data_num);
void UART4_Send (unsigned char *DataToSend ,u8 data_num);
void UART5_Send (unsigned char *DataToSend ,u8 data_num);

void usart1_send(u8 data);
void usart2_send(u8 data); 
void usart3_send(u8 data);
void uart4_send(u8 data);
void uart5_send(u8 data);

#endif




