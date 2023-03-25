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


void vTask1(void* pvParameters);
void vTask2(void* pvParameters);
void vTask3(void* pvParameters);

int main(void) {
    //priorities are changed so that the tasks run in the order T1, T3, T2
    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask3, "Task 3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    for (;; );
    return 0;
}

void vTask1(void* pvParameters) {
	const char* pcTaskName = "Task 1 is running\r\n";
	while (1) {
		printf(pcTaskName);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vTask2(void* pvParameters) {
    const char* pcTaskName = "Task 2 is running\r\n";
    while (1) {
        printf(pcTaskName);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTask3(void* pvParameters) {
    const char* pcTaskName = "Task 3 is running\r\n";
    while (1) {
        printf(pcTaskName);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
