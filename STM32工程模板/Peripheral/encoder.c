#include "encoder.h"


/*************************
*       ������           
*   ��ʱ��4��D12��D13
*     	 5��A0,A1
*************************/
void encoder_tim_init(void)
{
        GPIO_InitTypeDef            GPIO_Initstruc;
        TIM_TimeBaseInitTypeDef     TIM_TimeBaseInit_Struc;
        TIM_ICInitTypeDef           TIM_ICInit_Struc;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_encoder,ENABLE);// TIM4ʱ��ʹ��
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIO_encoder,ENABLE);//  GPIODʱ��ʹ��
       
        GPIO_PinAFConfig(GPIO_encoder,GPIO_PinSourceA,GPIO_AF_encoder);
        GPIO_PinAFConfig(GPIO_encoder,GPIO_PinSourceB,GPIO_AF_encoder);
       
        GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AF;
        GPIO_Initstruc.GPIO_OType=GPIO_OType_OD;
        GPIO_Initstruc.GPIO_Pin= GPIO_PinSourceA | GPIO_PinSourceB;
        GPIO_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_Initstruc.GPIO_Speed=GPIO_Speed_100MHz;
        GPIO_Init(GPIO_encoder,&GPIO_Initstruc);

        TIM_TimeBaseStructInit(&TIM_TimeBaseInit_Struc);
        TIM_TimeBaseInit_Struc.TIM_Prescaler=0x00;                  //��ʱ�����Ƶ
        TIM_TimeBaseInit_Struc.TIM_Period=0xffffffff;                     //�趨�������Զ���װֵ
        TIM_TimeBaseInit_Struc.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInit_Struc.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInit(encoder_tim,&TIM_TimeBaseInit_Struc);
       
        TIM_EncoderInterfaceConfig(encoder_tim,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);          //��ʼ��������TIM4ΪTI1���ؼ�����
       
        TIM_ICStructInit(&TIM_ICInit_Struc);                         //
        TIM_ICInit_Struc.TIM_ICFilter=8;                            //�����˲���
       
        TIM_ICInit(encoder_tim,&TIM_ICInit_Struc);
       
        TIM_ClearFlag(encoder_tim,TIM_FLAG_Update);
        TIM_ITConfig(encoder_tim,TIM_IT_Update,ENABLE);
        encoder_tim->CNT=0;
        TIM_Cmd(encoder_tim,ENABLE);//������ʱ��4
}


/**************************************************************************
�������ܣ���λʱ���ȡ����������
��� ֵ����ʱ��
���� ֵ��������
**************************************************************************/
float Read_Velocity()
{
    int encoder_num;
	float speed;
	encoder_num = (int)((int16_t)(encoder_tim->CNT)); // ����������Ҫע����������
	TIM_SetCounter(encoder_tim, 0);
	speed = ((float)encoder_num)/0.050/780*360; //0.05(ʱ��)/780(һȦ��������)*360(�Ƕ�)
	return speed;
}

void encoder_tim_init1(void)
{
        GPIO_InitTypeDef            GPIO_Initstruc;
        TIM_TimeBaseInitTypeDef     TIM_TimeBaseInit_Struc;
        TIM_ICInitTypeDef           TIM_ICInit_Struc;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);// TIM5ʱ��ʹ��
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//  GPIOAʱ��ʹ��
       
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);//����PA0��PA1Ϊ���ù���
       
        GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AF;
        GPIO_Initstruc.GPIO_OType=GPIO_OType_OD;
        GPIO_Initstruc.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
        GPIO_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_Initstruc.GPIO_Speed=GPIO_Speed_100MHz;
        GPIO_Init(GPIOA,&GPIO_Initstruc);

        TIM_TimeBaseStructInit(&TIM_TimeBaseInit_Struc);
        TIM_TimeBaseInit_Struc.TIM_Prescaler=0x00;                  //��ʱ�����Ƶ
        TIM_TimeBaseInit_Struc.TIM_Period=0xffffffff;                     //�趨�������Զ���װֵ
        TIM_TimeBaseInit_Struc.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInit_Struc.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInit_Struc);
       
        TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI1,
        TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);          //��ʼ��������TIM5ΪTI1���ؼ�����
       
        TIM_ICStructInit(&TIM_ICInit_Struc);                         //
        TIM_ICInit_Struc.TIM_ICFilter=8;                            //�����˲���
       
        TIM_ICInit(TIM5,&TIM_ICInit_Struc);
       
        TIM_ClearFlag(TIM5,TIM_FLAG_Update);
        TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
        TIM5->CNT=0;
        TIM_Cmd(TIM5,ENABLE);//������ʱ��5
}


/**************************************************************************
�������ܣ���λʱ���ȡ����������
��� ֵ����ʱ��
���� ֵ��������
**************************************************************************/

float Read_Velocity1()
{
	int encoder_num;
	float speed;
	encoder_num = (int)((int16_t)(TIM5->CNT)); // ����������Ҫע����������
	TIM_SetCounter(TIM5, 0);
	speed = ((float)encoder_num)/0.050/780*360; //0.05(ʱ��)/780(һȦ��������)*360(�Ƕ�)
	return speed;
}







