#include "ultr.h"
/**********************************/
/*          ������ģ��            */
/*********************************/
//PF10--Echo PF9--Trig
void ultr_Init(void)//��ʱ����IO�ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//ʹ�ܶ˿�Fʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��time4ʱ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; //���ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//�ܽ�����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//�ٶ�����
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF,&GPIO_InitStructure); //��ʼ���ṹ��
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);//��ʼ��trigΪ�͵�ƽ
	
	//PF10 echa�ܽų�ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//GPIOA_10�ܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;//����Ϊ����ģʽ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//�ٶ�����
	GPIO_Init(GPIOF,&GPIO_InitStructure); //��ʼ���ṹ��
	
	//��ʱ��4��ʼ��
	TIM_TimeBaseInitStructure.TIM_Period=500000-1;//��ʱ������
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;//��ʱԤ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//����ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ���ṹ��
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//��ʼ��ʱ�ӽṹ��
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//�жϱ�־���
	
}

void ultr_star(void)//����������ģ��
{
	GPIO_SetBits(GPIOF, GPIO_Pin_9);   //����pf9��ƽ
	
	delay_us(10);//����10us
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_9); //����pf9��ƽ
}

u32 ultr_return(void)//���س��������ص�ʱ��
{
//	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==1);
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
	ultr_star();
	TIM_SetCounter(TIM4,0);
	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==0);//�ȴ�ECho����
	TIM_Cmd(TIM4,ENABLE);
	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) == 1);//�ȴ�ECho����
	TIM_Cmd(TIM4,DISABLE);  //�رն�ʱ��
	return TIM_GetCounter(TIM4); //���ض�ʱ��ֵ
}

float ultr(void)//�������
{
	
	float l=0;
	l = (ultr_return() * 0.034)/2.0; //����=ʱ��*�ٶȣ�0.034us/cm��/2
	return l;
	
	
}




