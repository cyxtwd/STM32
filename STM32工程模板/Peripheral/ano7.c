#include "ano7.h"
/***************
*     ����v7   *
***************/
u8 BUFF[50];

/*
 ���ڷ��ͺ�����
 ���ֵ����Ҫ���͵����ݣ����ݵĳ���
 ����ֵ����
 ע�⣺��Ҫ�ȳ�ʼ������1
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
 ����v7ͨ��Э�飺
 ���ֵ����Ҫ���͵�����
 ����ֵ����
*/
void Test_Send_User(int16_t data1, int16_t data2, int16_t data3)
{
	int i;
	u8 sumcheck = 0;
	u8 addcheck = 0;
	u8 _cnt=0;
	BUFF[_cnt++]=0xAA;//֡ͷ
	BUFF[_cnt++]=0xFF;//Ŀ���ַ
	BUFF[_cnt++]=0XF1;//������
	BUFF[_cnt++]=0;//���ݳ���
	BUFF[_cnt++]=BYTE0(data1);//��������,С��ģʽ����λ��ǰ
	BUFF[_cnt++]=BYTE1(data1);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
	BUFF[_cnt++]=BYTE0(data2);
	BUFF[_cnt++]=BYTE1(data2);	
	BUFF[_cnt++]=BYTE0(data3);
	BUFF[_cnt++]=BYTE1(data3);
	BUFF[_cnt++]=0x00;
	BUFF[3] = _cnt-4;
	//SC��AC��У��
	for(i=0;i<BUFF[3]+4;i++) 
	{
		sumcheck+=BUFF[i];
		addcheck+=sumcheck;
	}
	BUFF[_cnt++]=sumcheck;	
	BUFF[_cnt++]=addcheck;	

	UART1_Send_Str(BUFF,_cnt);
	
}


