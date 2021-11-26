#include "encoder.h"


/*************************
*       编码器           
*   定时器4：D12，D13
*     	 5：A0,A1
*************************/
void encoder_tim_init(void)
{
        GPIO_InitTypeDef            GPIO_Initstruc;
        TIM_TimeBaseInitTypeDef     TIM_TimeBaseInit_Struc;
        TIM_ICInitTypeDef           TIM_ICInit_Struc;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_encoder,ENABLE);// TIM4时钟使能
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIO_encoder,ENABLE);//  GPIOD时钟使能
       
        GPIO_PinAFConfig(GPIO_encoder,GPIO_PinSourceA,GPIO_AF_encoder);
        GPIO_PinAFConfig(GPIO_encoder,GPIO_PinSourceB,GPIO_AF_encoder);
       
        GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AF;
        GPIO_Initstruc.GPIO_OType=GPIO_OType_OD;
        GPIO_Initstruc.GPIO_Pin= GPIO_PinSourceA | GPIO_PinSourceB;
        GPIO_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_Initstruc.GPIO_Speed=GPIO_Speed_100MHz;
        GPIO_Init(GPIO_encoder,&GPIO_Initstruc);

        TIM_TimeBaseStructInit(&TIM_TimeBaseInit_Struc);
        TIM_TimeBaseInit_Struc.TIM_Prescaler=0x00;                  //定时器与分频
        TIM_TimeBaseInit_Struc.TIM_Period=0xffffffff;                     //设定计数器自动重装值
        TIM_TimeBaseInit_Struc.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInit_Struc.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInit(encoder_tim,&TIM_TimeBaseInit_Struc);
       
        TIM_EncoderInterfaceConfig(encoder_tim,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);          //初始化编码器TIM4为TI1边沿技计数
       
        TIM_ICStructInit(&TIM_ICInit_Struc);                         //
        TIM_ICInit_Struc.TIM_ICFilter=8;                            //输入滤波器
       
        TIM_ICInit(encoder_tim,&TIM_ICInit_Struc);
       
        TIM_ClearFlag(encoder_tim,TIM_FLAG_Update);
        TIM_ITConfig(encoder_tim,TIM_IT_Update,ENABLE);
        encoder_tim->CNT=0;
        TIM_Cmd(encoder_tim,ENABLE);//启动定时器4
}


/**************************************************************************
函数功能：单位时间读取编码器计数
入口 值：定时器
返回 值：脉冲数
**************************************************************************/
float Read_Velocity()
{
    int encoder_num;
	float speed;
	encoder_num = (int)((int16_t)(encoder_tim->CNT)); // 这里尤其需要注意数据类型
	TIM_SetCounter(encoder_tim, 0);
	speed = ((float)encoder_num)/0.050/780*360; //0.05(时间)/780(一圈的脉冲数)*360(角度)
	return speed;
}

void encoder_tim_init1(void)
{
        GPIO_InitTypeDef            GPIO_Initstruc;
        TIM_TimeBaseInitTypeDef     TIM_TimeBaseInit_Struc;
        TIM_ICInitTypeDef           TIM_ICInit_Struc;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);// TIM5时钟使能
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//  GPIOA时钟使能
       
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);//设置PA0和PA1为复用功能
       
        GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AF;
        GPIO_Initstruc.GPIO_OType=GPIO_OType_OD;
        GPIO_Initstruc.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
        GPIO_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_Initstruc.GPIO_Speed=GPIO_Speed_100MHz;
        GPIO_Init(GPIOA,&GPIO_Initstruc);

        TIM_TimeBaseStructInit(&TIM_TimeBaseInit_Struc);
        TIM_TimeBaseInit_Struc.TIM_Prescaler=0x00;                  //定时器与分频
        TIM_TimeBaseInit_Struc.TIM_Period=0xffffffff;                     //设定计数器自动重装值
        TIM_TimeBaseInit_Struc.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInit_Struc.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInit_Struc);
       
        TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI1,
        TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);          //初始化编码器TIM5为TI1边沿技计数
       
        TIM_ICStructInit(&TIM_ICInit_Struc);                         //
        TIM_ICInit_Struc.TIM_ICFilter=8;                            //输入滤波器
       
        TIM_ICInit(TIM5,&TIM_ICInit_Struc);
       
        TIM_ClearFlag(TIM5,TIM_FLAG_Update);
        TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
        TIM5->CNT=0;
        TIM_Cmd(TIM5,ENABLE);//启动定时器5
}


/**************************************************************************
函数功能：单位时间读取编码器计数
入口 值：定时器
返回 值：脉冲数
**************************************************************************/

float Read_Velocity1()
{
	int encoder_num;
	float speed;
	encoder_num = (int)((int16_t)(TIM5->CNT)); // 这里尤其需要注意数据类型
	TIM_SetCounter(TIM5, 0);
	speed = ((float)encoder_num)/0.050/780*360; //0.05(时间)/780(一圈的脉冲数)*360(角度)
	return speed;
}







