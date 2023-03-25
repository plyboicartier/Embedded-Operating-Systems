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

int main(void) {
    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();

    for (;; );
    return 0;
}

void vTask1(void* pvParameters) {
    while (1) {
        printf("Task 1 is running\r\n");
        printf("Going to sleep for 30 ticks\r\n");
        vTaskDelay(30);
    }
}

void vTask2(void* pvParameters) {
    while (1) {
        printf("Task 2 is running\r\n");
        vTaskDelay(10);
    }
}