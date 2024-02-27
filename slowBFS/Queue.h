#ifndef TASK_2_QUEUE_H
#define TASK_2_QUEUE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;


void initQueue(Queue* q);
void enqueue(Queue* q, int data);
int dequeue(Queue* q, int* data);
int isEmpty(Queue* q);
void freeQueue(Queue* q);

#endif //TASK_2_QUEUE_H
