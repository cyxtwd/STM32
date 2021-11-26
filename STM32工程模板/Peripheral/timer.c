#include "timer.h"

/*  ����ʹ��AHB  APB1 APB2 ��rcc.h����鿴 */
//STM32F4 �ܶ������ʱ����Դ�������������ţ� APB1 �� APB2������ APB1�ǵ������ߣ���� 42Mhz����APB2 �Ǹ������ߣ���� 84Mhz����
/*����*///��ʱ�� /*���֣�����������ߣ� APB1/APB2���ķ�Ƶϵ��Ϊ 1����ô�Ͳ���Ƶ�������Ϊ 1������ 2/4/8/16������ô�ͻ� 2 ��Ƶ����Ϊ��ʱ��ʱ�����롣
//�򵥵�˵���ٸ�APB1�����ӣ�ϵͳʱ����168Mhz,APB1��Ƶϵ��Ϊ4��system_stm32f4xx.c���ã���
//��APB1�ٶ�Ϊ42Mhz,���ǹҿ��ڸ������ϵĶ�ʱ��3�����ڷ�Ƶϵ��4������1����˶�ʱ������Ƶ��Ϊ42Mhz x 2 =84 Mhz*/


/***************************************************************************** 
ͨ�ö�ʱ��3�жϳ�ʼ��
arr���Զ���װֵ��
psc��ʱ��Ԥ��Ƶ��
��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
Ft=��ʱ������Ƶ��,��λ:Mhz							 
******************************************************************************/

void TIM3_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�Ӳ���Ƶ  84M 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
	
}

//��ʱ��3�жϷ�����

void TIM3_IRQ(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		//your code here��
		/* PID */
		int Encoder,Moto;		
		Encoder=Read_Velocity();  
		Moto=Incremental_PI(Encoder,pid); 
		TIM2->CNT=Moto;
		Test_Send_User(Encoder,pid.Value,0);

	}TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
	
}
/******************************************************************************
ͨ�ö�ʱ��2�жϳ�ʼ��
arr���Զ���װֵ��
psc��ʱ��Ԥ��Ƶ��
��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
Ft=��ʱ������Ƶ��,��λ:Mhz
******************************************************************************/

void TIM2_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�Ӳ���Ƶ  84M 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��2
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
	
}

extern float pitch,roll,yaw; 		
//��ʱ��2�жϷ�����
void TIM2_IRQ(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		//your code here��
		/* ������ */
//		Read_DMP(&pitch,&roll,&yaw);
//		Test_Send_User(pitch,roll,yaw,0,0,0);
//		LED_Grn=~LED_Grn;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}

/******************************************************************************
ͨ�ö�ʱ��4�жϳ�ʼ��
arr���Զ���װֵ��
psc��ʱ��Ԥ��Ƶ��
��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
Ft=��ʱ������Ƶ��,��λ:Mhz                           
******************************************************************************/

void TIM4_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�Ӳ���Ƶ  84M 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��4�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
	
}

//��ʱ��4�жϷ�����
void TIM4_IRQ(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		//your code here��

			
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}
/******************************************************************************
ͨ�ö�ʱ��5�жϳ�ʼ��
arr���Զ���װֵ��
psc��ʱ��Ԥ��Ƶ��
��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
Ft=��ʱ������Ƶ��,��λ:Mhz                          
******************************************************************************/



void TIM5_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�Ӳ���Ƶ  84M 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��5�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
	
}

//��ʱ��5�жϷ�����
void TIM5_IRQ(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		//your code here��
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}

/******************************************************************************/
/*                  			 ��ʱ����ʼ����װ                             */
/******************************************************************************/
void TIMx_Timer_Init(u8 x,u32 time)
{
	switch(x)
	{
		case 2:TIM2_Timer_Init(time-1,84-1);break;
		case 3:TIM3_Timer_Init(time-1,84-1);break;
		case 4:TIM4_Timer_Init(time-1,84-1);break;
		case 5:TIM5_Timer_Init(time-1,84-1);break;
		
		
	}
}


