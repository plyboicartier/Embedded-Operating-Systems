/*
*	Carter Glynn
*	EECE2617 Embedded OS - Lab 2: Part B
*	2023-03-13
*/
#include <stdio.h>
#include <conio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

/* Shared int Declaration  */
int shared;

/* Task Declarations  */
void vTaskA(void);
void vTaskB(void);

SemaphoreHandle_t sharedSemaphore;


int main() {
	/*  Initialize Shared Variable and Semaphore */
	shared = 100;
	sharedSemaphore = xSemaphoreCreateBinary();
	/* Initialize Semaphore to available state */
	xSemaphoreGive(sharedSemaphore);
	/*  Create Task A  */
	xTaskCreate(vTaskA, "TASK_A", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	/*  Create Task B  */
	xTaskCreate(vTaskB, "TASK_B", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	/*  Start Scheduler  */
	vTaskStartScheduler();
	return 0;
}

void vTaskA() {
	while (1) {
		/* wait for semaphore to become available */
		xSemaphoreTake(sharedSemaphore, portMAX_DELAY);

		/* increment shared variable */
		shared++;

		/* release semaphore */
		xSemaphoreGive(sharedSemaphore);

		/* delay for Task B to run (and for visibility) */
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void vTaskB() {
	while (1) {
		/* wait for semaphore to become available */
		xSemaphoreTake(sharedSemaphore, portMAX_DELAY);

		/* increment shared variable */
		printf("Task B shared variable is %d\n", shared);

		/* release semaphore */
		xSemaphoreGive(sharedSemaphore);

		/* delay for Task B to run (and for visibility) */
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}