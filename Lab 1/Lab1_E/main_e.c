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

int main(void) {
	xTaskCreate(vTask1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(vTask2, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
	for (;;);
	return 0;
}

void vTask1(void* pvParameters) {
	const char* pcTaskName = "Task 1 is running\r\n";
	while (1) {
		printf(pcTaskName);
		vTaskDelay(30); //delayed so task 2 isn't starved (runs once)
	}
}
void vTask2(void* pvParameters) {
	const char* pcTaskName = "Task 2 is running\r\n";
	while (1) {
		//no delay so task 1 is starved
		printf(pcTaskName);
	}
}
