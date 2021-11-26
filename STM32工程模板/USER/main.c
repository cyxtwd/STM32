#include "Include.h"

//APB1-42MHz  APB2-84MHz   AHB-168MHz 
TaskHandle_t StartTask_Handler;         //任务句柄
TaskHandle_t test1_Handler;		//任务句柄	
TaskHandle_t test2_Handler;		//任务句柄	
TaskHandle_t test3_Handler;		//任务句柄
TaskHandle_t test4_Handler;		//任务句柄
int main(void)
{
	System_Init();
		//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄  
	
	vTaskStartScheduler();   //启动任务调度
	
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
	
	xTaskCreate( test1, "test1", Data1_STK_SIZE, NULL, Data1_TASK_PRIO, &test1_Handler);      //创建一个任务
	xTaskCreate( test2, "test2", Data2_STK_SIZE, NULL, Data2_TASK_PRIO, &test2_Handler );
	xTaskCreate( test3, "test3", Data3_STK_SIZE, NULL, Data3_TASK_PRIO, &test3_Handler );
	xTaskCreate( test4, "test4", Data4_STK_SIZE, NULL, Data4_TASK_PRIO, &test4_Handler ); 

	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();            //退出临界区
}



