//
// Created by tomer on 14/02/2024.
//

#ifndef TARGIL_2_BFS_H
#define TARGIL_2_BFS_H
#include "./SyncGraph/graph.h"
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

// Queue implementation for BFS
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    vertex* array;
} Queue;

Queue* createQueue(unsigned capacity);

bool isFull(Queue* queue);

bool isEmptySlowBfs(Queue* queue);

void enqueue(Queue* queue, vertex item);

vertex dequeue(Queue* queue);
void runSlowBfs(Graph *graph, int **m);
void bfsSlow(Graph* graph, int **m, int source);
#endif //TARGIL_2_BFS_H
