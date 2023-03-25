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

static const char *pcTextForTask1 = "Task 1 is running\r\n";

int main(void) {
	xTaskCreate(vTask1, "TASK_1", configMINIMAL_STACK_SIZE, (void*)pcTextForTask1, 1, NULL);
	vTaskStartScheduler();
	for (;;);
	return 0;
}

void vTask1(void* pvParameters) {
	char* pcTaskName;
	pcTaskName = (char*)pvParameters;
	while(1) {
		printf(pcTaskName);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
