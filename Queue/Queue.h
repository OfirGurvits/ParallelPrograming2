// 325655058 ofir gurvits
// 323082867 Shaked Solomon

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


void init_Queue(Queue* q);
void enqueue(Queue* q, int data);
int dequeue(Queue* q, int* data);
int is_Empty(Queue* q);
void freeQueue(Queue* q);

#endif //TASK_2_QUEUE_H
