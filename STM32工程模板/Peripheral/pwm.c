#include "pwm.h"

/*  ����ʹ��AHB  APB1 APB2 ��rcc.h����鿴 */
//STM32F4 �ܶ������ʱ����Դ�������������ţ� APB1 �� APB2������ APB1�ǵ������ߣ���� 42Mhz����APB2 �Ǹ������ߣ���� 84Mhz����
/*����*///��ʱ�� /*���֣�����������ߣ� APB1/APB2���ķ�Ƶϵ��Ϊ 1����ô�Ͳ���Ƶ�������Ϊ 1������ 2/4/8/16������ô�ͻ� 2 ��Ƶ����Ϊ��ʱ��ʱ�����롣
//�򵥵�˵���ٸ�APB1�����ӣ�ϵͳʱ����168Mhz,APB1��Ƶϵ��Ϊ4��system_stm32f4xx.c���ã���
//��APB1�ٶ�Ϊ42Mhz,���ǹҿ��ڸ������ϵĶ�ʱ��3�����ڷ�Ƶϵ��4������1����˶�ʱ������Ƶ��Ϊ42Mhz x 2 =84 Mhz*/

#define INIT_DUTY 0


void TIM2_PWM_Init(u32 arr,u32 psc,u8 mode)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_OCStructInit(&TIM_OCInitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//TIM2ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//GPIOAʱ��ʹ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	  
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);//GPIOA0����Ϊ��ʱ��2
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);



	TIM_TimeBaseStructure.TIM_Period = arr;		      //�����Զ���װ��ֵ							
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	      //����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //��ʼ��TIM2
	
        /**********************************************/
	/*����TIM2_CH1��PWMģʽ������TIMָ���Ĳ�����ʼ������TIM2 4OC1~4*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����ģʽΪPWMģʽ
	if(mode==PWM_Polarity_High)//���ü��Ըߵ�
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//	/**** ʹ��TIM2��CH1��� ****/
//	/* PWM1 Mode configuration: Channel1 */
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
//	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//����Tָ���Ĳ�����ʼ������TIM2 4OC1

//	/* PWM1 Mode configuration: Channel2 */
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//����Tָ���Ĳ�����ʼ������TIM2 4OC2

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//����Tָ���Ĳ�����ʼ������TIM2 4OC3

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//����Tָ���Ĳ�����ʼ������TIM2 4OC4

	TIM_ARRPreloadConfig(TIM2, ENABLE);//ARPEʹ��
	TIM_Cmd(TIM2, ENABLE);//ʹ��TIM2
	
	
}
void TIM3_PWM_Init(u32 arr,u32 psc,u8 mode)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	  
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
	

  TIM_TimeBaseStructure.TIM_Period = arr;									
  TIM_TimeBaseStructure.TIM_Prescaler = psc;		
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   if(mode==PWM_Polarity_High)
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
   else 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
	
}

void TIM4_PWM_Init(u32 arr,u32 psc,u8 mode)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
	

  TIM_TimeBaseStructure.TIM_Period = arr;									
  TIM_TimeBaseStructure.TIM_Prescaler = psc;		
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   if(mode==PWM_Polarity_High)
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
   else 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

void TIM5_PWM_Init(u32 arr,u32 psc,u8 mode)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_TIM5);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_TIM5);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_TIM5);
	

  TIM_TimeBaseStructure.TIM_Period = arr;									
  TIM_TimeBaseStructure.TIM_Prescaler = psc;		
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   if(mode==PWM_Polarity_High)
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
   else 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC3Init(TIM5, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
  TIM_OC4Init(TIM5, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM5, ENABLE);
  TIM_Cmd(TIM5, ENABLE);
}

void PWM2_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value)
{
	TIM2->CCR1 = CH1_Value;
	TIM2->CCR2 = CH2_Value;
	TIM2->CCR3 = CH3_Value;
	TIM2->CCR4 = CH4_Value;
}
void PWM3_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value)
{
	TIM3->CCR1 = CH1_Value;
	TIM3->CCR2 = CH2_Value;
	TIM3->CCR3 = CH3_Value;
	TIM3->CCR4 = CH4_Value;
}

void PWM4_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value)
{
	TIM4->CCR1 = CH1_Value;
	TIM4->CCR2 = CH2_Value;
	TIM4->CCR3 = CH3_Value;
	TIM4->CCR4 = CH4_Value;
}
void PWM5_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value)
{
	TIM5->CCR1 = CH1_Value;
	TIM5->CCR2 = CH2_Value;
	TIM5->CCR3 = CH3_Value;
	TIM5->CCR4 = CH4_Value;
}
