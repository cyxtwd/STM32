#include "Include.h"

//APB1-42MHz  APB2-84MHz   AHB-168MHz 
TaskHandle_t StartTask_Handler;         //������
TaskHandle_t test1_Handler;		//������	
TaskHandle_t test2_Handler;		//������	
TaskHandle_t test3_Handler;		//������
TaskHandle_t test4_Handler;		//������
int main(void)
{
	System_Init();
		//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������  
	
	vTaskStartScheduler();   //�����������
	
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
	
	xTaskCreate( test1, "test1", Data1_STK_SIZE, NULL, Data1_TASK_PRIO, &test1_Handler);      //����һ������
	xTaskCreate( test2, "test2", Data2_STK_SIZE, NULL, Data2_TASK_PRIO, &test2_Handler );
	xTaskCreate( test3, "test3", Data3_STK_SIZE, NULL, Data3_TASK_PRIO, &test3_Handler );
	xTaskCreate( test4, "test4", Data4_STK_SIZE, NULL, Data4_TASK_PRIO, &test4_Handler ); 

	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL();            //�˳��ٽ���
}



