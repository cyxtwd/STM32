#include "ultr.h"
/**********************************/
/*          超声波模块            */
/*********************************/
//PF10--Echo PF9--Trig
void ultr_Init(void)//定时器，IO口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//使能端口F时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能time4时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; //输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度设置
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure); //初始化结构体
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);//初始化trig为低电平
	
	//PF10 echa管脚初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//GPIOA_10管脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;//设置为输入模式
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//下拉
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度设置
	GPIO_Init(GPIOF,&GPIO_InitStructure); //初始化结构体
	
	//定时器4初始化
	TIM_TimeBaseInitStructure.TIM_Period=500000-1;//定时器周期
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;//定时预分频器
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化结构体
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//初始化时钟结构体
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//中断标志清除
	
}

void ultr_star(void)//启动超声波模块
{
	GPIO_SetBits(GPIOF, GPIO_Pin_9);   //拉高pf9电平
	
	delay_us(10);//持续10us
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_9); //拉低pf9电平
}

u32 ultr_return(void)//返回超声波来回的时间
{
//	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==1);
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
	ultr_star();
	TIM_SetCounter(TIM4,0);
	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==0);//等待ECho拉低
	TIM_Cmd(TIM4,ENABLE);
	while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10) == 1);//等待ECho拉高
	TIM_Cmd(TIM4,DISABLE);  //关闭定时器
	return TIM_GetCounter(TIM4); //返回定时器值
}

float ultr(void)//计算距离
{
	
	float l=0;
	l = (ultr_return() * 0.034)/2.0; //距离=时间*速度（0.034us/cm）/2
	return l;
	
	
}




