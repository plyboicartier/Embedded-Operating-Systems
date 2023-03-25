/*
*	Carter Glynn
*	EECE2617 Embedded OS - Lab 2: Part A
*	2023-03-13
*/
#include <stdio.h>
#include <conio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#define QUEUE_LENGTH 5		// define length of queue
#define MESSAGE_VALUE 100	// define value of message

/*  FUNCTION DECLARATIONS  */
void vTaskA(void);
void vTaskB(void);

/*  Structure Definition  */
typedef struct {
    int message;
    TaskFunction_t task;
} Message;

xQueueHandle messageQueue;

int main(void) {
	/*  Create Queue  */
	messageQueue = xQueueCreate(QUEUE_LENGTH, sizeof(Message));
	/*  Create Task A  */
	xTaskCreate(vTaskA, "TASK_A", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	/*  Create Task B  */
	xTaskCreate(vTaskB, "TASK_B", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	/*  Start Scheduler  */
	vTaskStartScheduler();
	return 0;
}

/*  Task A Definition  */
void vTaskA(void* pvParameters) {
	/*  Create sMessage structure  */
	Message sMessage = {
			.message = MESSAGE_VALUE,
			.task = vTaskA,
	};
	
	while (1) {
		/*  Send message to Task B  */ 
		xQueueSendToBack(messageQueue, &sMessage, 0);
		printf("Task A sent message with value %d\nQueue length before receive is %d\n\n", sMessage.message, uxQueueMessagesWaiting(messageQueue));

		/*  Take in acknowledgement structure  */
		Message rMessage;
		/*  Don't run anything further until Task B sends back acknowledgement  */
		while (xQueuePeek(messageQueue, &rMessage, 0) != pdTRUE || rMessage.task != vTaskB) {} // look at queue and populate rMessage
		
		/*  Wait for acknowledgement from Task B  */ 
		xQueueReceive(messageQueue, &rMessage, 0);
		printf("Task A received acknowledgement with value %d\nQueue length after receive is %d\n\n", rMessage.message, uxQueueMessagesWaiting(messageQueue));
		
		vTaskDelay(pdMS_TO_TICKS(500)); // delay for console visibility
	}
}

/*  Task B Definition  */
void vTaskB(void* pvParameters) {
	BaseType_t xStatus;
	while (1) {
		/*  Don't run anything further until Task A sends message  */
		Message rMessage;
		while (xQueuePeek(messageQueue, &rMessage, 0) != pdTRUE || rMessage.task != vTaskA) {} // look at queue and populate rMessage

		/*  Wait for message from Task A  */ 
		xStatus = xQueueReceive(messageQueue, &rMessage, 0);
		if (xStatus == pdPASS) {
			printf("Task B received message \"%d\"\nQueue length before send is %d\n\n", rMessage.message, uxQueueMessagesWaiting(messageQueue));
			/*  Create acknowledgement structure */
			Message acknowledgement = {
				.message = 1,
				.task = vTaskB,
			};
			/*  Send acknowledgement to Task A  */
			xQueueSendToBack(messageQueue, &acknowledgement, 0);
			printf("Task B sent acknowledgement with value %d\nQueue length after send is %d\n\n", acknowledgement.message, uxQueueMessagesWaiting(messageQueue));
		}
	}
}
