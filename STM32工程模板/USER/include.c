#include "Include.h"
/****************************************/
//			系统初始化函数							
/****************************************/
void System_Init()
{
   /*******系统配置********/
	SysTick_ConfigInit();//配置滴答定时器，用于延时函数 delay_nms();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
   /***********************/
    
   /*******用户配置********/
   LED_Init();
   KEY_Init();
	BEEP_Init();
	RGB_LED_Init();
   USART1_Init(115200);
   AD_Init(ADC_Channel_0);
   AD_Init(ADC_Channel_1);
   AD_Init(ADC_Channel_2);
   AD_Init(ADC_Channel_3);
	Coefficient_Init();
   TIM3_PWM_Init(5000-1,8400-1,1);
   /***********************/   
}
/****************************************/
//					任务函数							
/****************************************/
void test1( void * pvParameters )
{
	u32 lastWakeTime = getSysTickCnt();
    while(1)
    {
       vTaskDelay(1000/portTICK_RATE_MS);
//		 vTaskDelayUntil(&lastWakeTime, M2T(RATE_1_HZ)); //此任务以1Hz的频率运行（1000ms控制一次）
       LED_Grn = ~LED_Grn;
		 printf("i am vTaskLed_G\r\n");
    }
}
void test2(void *pvParameters )
{
	u32 lastWakeTime = getSysTickCnt();
	while(1)
	{
		vTaskDelay(500 / portTICK_RATE_MS); //此任务以2Hz的频率运行（500ms控制一次）
		RGB_Grn = ~RGB_Grn;
	}
}
void test3(void *pvParameters )
{
	while(1)
	{
		vTaskDelay(5000 / portTICK_RATE_MS);	//5s控制一次
		BEEP = BEEP_ON;
		vTaskDelay(50 / portTICK_RATE_MS);
		BEEP = BEEP_OFF;
	}
}
void test4(void *pvParameters )
{
	while(1)
	{
		vTaskDelay(1000 / portTICK_RATE_MS);
		RGB_Red = ~RGB_Red;
	}
}



