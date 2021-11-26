#include "Include.h"
/****************************************/
//			ϵͳ��ʼ������							
/****************************************/
void System_Init()
{
   /*******ϵͳ����********/
	SysTick_ConfigInit();//���õδ�ʱ����������ʱ���� delay_nms();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
   /***********************/
    
   /*******�û�����********/
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
//					������							
/****************************************/
void test1( void * pvParameters )
{
	u32 lastWakeTime = getSysTickCnt();
    while(1)
    {
       vTaskDelay(1000/portTICK_RATE_MS);
//		 vTaskDelayUntil(&lastWakeTime, M2T(RATE_1_HZ)); //��������1Hz��Ƶ�����У�1000ms����һ�Σ�
       LED_Grn = ~LED_Grn;
		 printf("i am vTaskLed_G\r\n");
    }
}
void test2(void *pvParameters )
{
	u32 lastWakeTime = getSysTickCnt();
	while(1)
	{
		vTaskDelay(500 / portTICK_RATE_MS); //��������2Hz��Ƶ�����У�500ms����һ�Σ�
		RGB_Grn = ~RGB_Grn;
	}
}
void test3(void *pvParameters )
{
	while(1)
	{
		vTaskDelay(5000 / portTICK_RATE_MS);	//5s����һ��
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



