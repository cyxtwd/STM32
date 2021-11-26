#include "ano7.h"
/***************
*     匿名v7   *
***************/
u8 BUFF[50];

/*
 串口发送函数：
 入口值：需要发送的数据，数据的长度
 返回值：无
 注意：需要先初始化串口1
*/
void UART1_Send_Str(u8 *s,u8 cnt)
{
	unsigned char i=0;
	while(i<cnt)
	{
		USART_SendData(USART1,s[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
		i++;
	}
	
}
/*
 匿名v7通信协议：
 入口值：需要发送的数据
 返回值：无
*/
void Test_Send_User(int16_t data1, int16_t data2, int16_t data3)
{
	int i;
	u8 sumcheck = 0;
	u8 addcheck = 0;
	u8 _cnt=0;
	BUFF[_cnt++]=0xAA;//帧头
	BUFF[_cnt++]=0xFF;//目标地址
	BUFF[_cnt++]=0XF1;//功能码
	BUFF[_cnt++]=0;//数据长度
	BUFF[_cnt++]=BYTE0(data1);//数据内容,小段模式，低位在前
	BUFF[_cnt++]=BYTE1(data1);//需要将字节进行拆分，调用上面的宏定义即可。
	BUFF[_cnt++]=BYTE0(data2);
	BUFF[_cnt++]=BYTE1(data2);	
	BUFF[_cnt++]=BYTE0(data3);
	BUFF[_cnt++]=BYTE1(data3);
	BUFF[_cnt++]=0x00;
	BUFF[3] = _cnt-4;
	//SC和AC的校验
	for(i=0;i<BUFF[3]+4;i++) 
	{
		sumcheck+=BUFF[i];
		addcheck+=sumcheck;
	}
	BUFF[_cnt++]=sumcheck;	
	BUFF[_cnt++]=addcheck;	

	UART1_Send_Str(BUFF,_cnt);
	
}


