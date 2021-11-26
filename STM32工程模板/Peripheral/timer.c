#include "timer.h"

/*  外设使用AHB  APB1 APB2 在rcc.h里面查看 */
//STM32F4 很多外设的时钟来源，即两个总线桥： APB1 和 APB2，其中 APB1是低速总线（最高 42Mhz），APB2 是高速总线（最高 84Mhz）。
/*另外*///定时器 /*部分，如果所在总线（ APB1/APB2）的分频系数为 1，那么就不倍频，如果不为 1（比如 2/4/8/16），那么就会 2 倍频后，作为定时器时钟输入。
//简单点说，举个APB1的例子，系统时钟是168Mhz,APB1分频系数为4（system_stm32f4xx.c配置），
//则APB1速度为42Mhz,但是挂靠在该总线上的定时器3，由于分频系数4而不是1，因此定时器输入频率为42Mhz x 2 =84 Mhz*/


/***************************************************************************** 
通用定时器3中断初始化
arr：自动重装值。
psc：时钟预分频数
定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
Ft=定时器工作频率,单位:Mhz							 
******************************************************************************/

void TIM3_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟不分频  84M 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
}

//定时器3中断服务函数

void TIM3_IRQ(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		//your code here。
		/* PID */
		int Encoder,Moto;		
		Encoder=Read_Velocity();  
		Moto=Incremental_PI(Encoder,pid); 
		TIM2->CNT=Moto;
		Test_Send_User(Encoder,pid.Value,0);

	}TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
	
}
/******************************************************************************
通用定时器2中断初始化
arr：自动重装值。
psc：时钟预分频数
定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
Ft=定时器工作频率,单位:Mhz
******************************************************************************/

void TIM2_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟不分频  84M 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE); //使能定时器2
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
}

extern float pitch,roll,yaw; 		
//定时器2中断服务函数
void TIM2_IRQ(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		//your code here。
		/* 陀螺仪 */
//		Read_DMP(&pitch,&roll,&yaw);
//		Test_Send_User(pitch,roll,yaw,0,0,0);
//		LED_Grn=~LED_Grn;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}

/******************************************************************************
通用定时器4中断初始化
arr：自动重装值。
psc：时钟预分频数
定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
Ft=定时器工作频率,单位:Mhz                           
******************************************************************************/

void TIM4_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟不分频  84M 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
}

//定时器4中断服务函数
void TIM4_IRQ(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		//your code here。

			
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}
/******************************************************************************
通用定时器5中断初始化
arr：自动重装值。
psc：时钟预分频数
定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
Ft=定时器工作频率,单位:Mhz                          
******************************************************************************/



void TIM5_Timer_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //时钟不分频  84M 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器5更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
}

//定时器5中断服务函数
void TIM5_IRQ(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		//your code here。
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

/******************************************************************************/
/*                  			 定时器初始化封装                             */
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


