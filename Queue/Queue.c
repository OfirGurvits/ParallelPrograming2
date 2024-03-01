// 325655058 ofir gurvits
// 323082867 Shaked Solomon

#include "Queue.h"
void init_Queue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q, int* data) {
    if (q->front == NULL) {
        return 0; // Queue is empty
    }

    QueueNode* temp = q->front;
    *data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return 1; // Success
}

int is_Empty(Queue* q) {
    return q->front == NULL;
}

void freeQueue(Queue* q) {
    QueueNode* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}
