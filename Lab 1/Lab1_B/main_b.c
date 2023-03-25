/*
*	Carter Glynn
*	EECE2617 Embedded OS - Lab 1
*	2023-02-12
*/
#include <stdio.h>
#include <conio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

void vTask1(void);
void vTask2(void);
void vTask3(void);

int main(void) {
	xTaskCreate(vTask1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(vTask2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}

void vTask1(void* pvParameters){
	const char* pcTaskName = "Task 1 is running\r\n";
	while (1) {
		printf(pcTaskName);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vTask2(void* pvParameters){
	const char* pcTaskName = "Task 2 is running\r\n";
	while (1)
	{
		printf(pcTaskName);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vTask3(void* pvParameters){
	const char* pcTaskName = "Task 3 is running\r\n";
	while (1) {
		printf(pcTaskName);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

TaskHandle_t vTask3Handle = NULL; //init task 3 handle
void vApplicationIdleHook(void) {
	if (vTask3Handle == NULL) { //stops task 3 from running more than once
		xTaskCreate(vTask3, "Task 3", configMINIMAL_STACK_SIZE, 1, 1, &vTask3Handle);
	}
}
