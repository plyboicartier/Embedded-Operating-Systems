#include "stdio.h"
#include "stdlib.h"

//Element struct
struct element {
    int id;
    int priority;
    struct element *next;
};

//Queue struct
struct Queue {
    struct element *front;
    struct element *rear;
};

//Queue init
struct Queue *CreateQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

//Element creation function, assigns variables and returns element
struct element *CreateElement(int priority) {
    static int ID = 1;
    struct element* element = (struct element*)malloc(sizeof(struct element));
    element->id = ID;
    ID++;
    element->priority = priority;
    element->next = NULL;
    return element;
}

//Adds element to queue, tests if queue exists, iterates through queue until place is found
void AddElement(struct Queue *q, int priority) {
    struct element* newElement = CreateElement(priority);
    if (q->rear == NULL) {
        q->front = newElement;
        q->rear = newElement;
        return;
    }
    struct element* temp = q->front;
    if (temp->priority <= priority) {
        newElement->next = temp;
        q->front = newElement;
    }
    else {
        while (temp->next != NULL && temp->next->priority > priority) {
            temp = temp->next;
        }
        newElement->next = temp->next;
        temp->next = newElement;
    }
}

//Removes element from queue by popping it off the front, frees the memory
void RemoveElement(struct Queue *q) {
    if (q->front == NULL) {
        printf("\nQueue is empty\n");
        return;
    }
    struct element* temp = q->front;
    q->front = q->front->next;
    printf("\nRemoved Element: ID = %d, Priority = %d\n", temp->id, temp->priority);
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
}

//Iterates through and displays all elements in queue
void DisplayElements(struct Queue *q) {
    if (q->front == NULL) {
        printf("\nQueue is empty\n");
        return;
    }
    struct element* temp = q->front;
    printf("\nQueue Elements: \n");
    while (temp != NULL) {
        printf("ID = %d, Priority = %d\n", temp->id, temp->priority);
        temp = temp->next;
    }
}

//Frees all memory allocated to queue
void ClearQueue(struct Queue *q) {
    struct element* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

int main()
{
    struct Queue* q = CreateQueue();
    int choice;
    int priority;
    while (1) {
        printf("\n1. Add element\n");
        printf("2. Remove element\n");
        printf("3. Display elements\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter priority: ");
            scanf_s("%d", &priority);
            //Validates if priority is okay
            if (priority <= 10 && priority >= 1) {
                AddElement(q, priority);
            }
            else {
                printf("\nInvalid priority, must be from 1-10");
                break;
            }
            break;
        case 2:
            RemoveElement(q);
            break;
        case 3:
            DisplayElements(q);
            break;
        case 4:
            ClearQueue(q);
            return 0;
            break;
        default:
            printf("\nInvalid choice\n");
            break;
        }
    }
    return 0;
}
