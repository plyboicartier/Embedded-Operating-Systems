#include "stdio.h"
#include "stdlib.h"

struct element {
    int id;
    int priority;
    struct element* next;
};

struct Stack {
    struct element* top;
};

struct Stack* CreateStack() {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->top = NULL;
    return s;
}

struct element* CreateElement(int priority) {
    static int ID = 1;
    struct element* element = (struct element*)malloc(sizeof(struct element));
    element->id = ID;
    ID++;
    element->priority = priority;
    element->next = NULL;
    return element;
}

void AddElement(struct Stack* s, int priority) {
    struct element* newElement = CreateElement(priority);
    if (s->top == NULL || s->top->priority <= priority) {
        newElement->next = s->top;
        s->top = newElement;
    }
    else {
        struct element* temp = s->top;
        while (temp->next != NULL && temp->next->priority > priority) {
            temp = temp->next;
        }
        newElement->next = temp->next;
        temp->next = newElement;
    }
}

void RemoveElement(struct Stack* s) {
    if (s->top == NULL) {
        printf("\nStack is empty\n");
        return;
    }
    struct element* temp = s->top;
    s->top = s->top->next;
    printf("\nRemoved Element: ID = %d, Priority = %d\n", temp->id, temp->priority);
    free(temp);
}

void DisplayElements(struct Stack* s) {
    if (s->top == NULL) {
        printf("\nStack is empty\n");
        return;
    }
    struct element* temp = s->top;
    printf("\nStack Elements: \n");
    while (temp != NULL) {
        printf("ID = %d, Priority = %d\n", temp->id, temp->priority);
        temp = temp->next;
    }
}

void ClearStack(struct Stack* s) {
    struct element* temp;
    while (s->top != NULL) {
        temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
}

int main() {
    struct Stack* s = CreateStack();
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
            if (priority <= 10 && priority >= 1) {
                AddElement(s, priority);
            }
            else {
                printf("\nInvalid priority, must be from 1-10\n");
                break;
            }
            break;
        case 2:
            RemoveElement(s);
            break;
        case 3:
            DisplayElements(s);
            break;
        case 4:
            ClearStack(s);
            return 0;
            break;
        default:
            printf("\nInvalid choice\n");
            break;
        }
    }
    return 0;
}