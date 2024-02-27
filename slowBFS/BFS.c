//
// Created by tomer on 14/02/2024.
//

#include "BFS.h"
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue
    queue->array = (vertex*)malloc(queue->capacity * sizeof(vertex));
    return queue;
}

bool isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmptySlowBfs(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, vertex item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

vertex dequeue(Queue* queue) {
    if (isEmptySlowBfs(queue)) return INT_MIN;
    vertex item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
void runSlowBfs(Graph *graph, int **m){
    // Run BFS for each vertex in the graph
    for (int sourceVertex = 0; sourceVertex < graph->numVertices; sourceVertex++) {
        // Queue for BFS
        Queue *queue = createQueue(graph->numVertices);

        // Array to mark visited vertices
        bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
        int* matrixRow = m[sourceVertex];
        for (int i = 0; i < graph->numVertices; i++){
            visited[i] = false;
            matrixRow[i] = -1;
        }

        // Mark the source vertex as visited and enqueue it
        visited[sourceVertex] = true;
        enqueue(queue, sourceVertex);
        m[sourceVertex][sourceVertex] = 0; // Distance from the vertex to itself is 0.
        while (!isEmptySlowBfs(queue)) {
            int currentVertex = dequeue(queue);

            // Traverse adjacency list of the current vertex
            // and process its neighbors
            node *temp = graph->adjacencyLists[currentVertex];
            while (temp != NULL) {
                int adjVertex = temp->v;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    enqueue(queue, adjVertex);
                    m[sourceVertex][adjVertex] = m[sourceVertex][currentVertex] + 1; // Distance of adjacent vertex is 1 more than the current one.
                }
                temp = temp->next;
            }
        }

        // Cleanup
        free(visited);
        free(queue->array);
        free(queue);
    }
}

void bfsSlow(Graph *graph, int **m, int source) {
    // Queue for BFS
    Queue *queue = createQueue(graph->numVertices);

    // Array to mark visited vertices
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    // Mark the source vertex as visited and enqueue it
    visited[0] = true;
    enqueue(queue, source);
    m[source][source] = 0; // Distance from vertex 0 to itself is 0.

    while (!isEmptySlowBfs(queue)) {
        int currentVertex = dequeue(queue);

        // Traverse adjacency list of the current vertex
        // and process its neighbors
        node *temp = graph->adjacencyLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->v;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
                m[source][adjVertex] = m[source][currentVertex] + 1; // Distance of adjacent vertex is 1 more than the current one.
            }
            temp = temp->next;
        }
    }

    // Cleanup
    free(visited);
    free(queue->array);
    free(queue);
}

