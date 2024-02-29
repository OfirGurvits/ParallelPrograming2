// 325655058 ofir gurvits
// 323082867 Shaked Solomon

#include "SyncGraph/graph.h"
#include "ThreadPool/ThreadPool.h"
#include "ThreadPool/TaskQueue.h"
#include "Queue/Queue.h"

struct graphArgs {
    Graph *graph;
    ThreadPool *q;
    int **m;
};
typedef struct graphArgs graphArgs;

struct bfsArgs {
    Graph *graph;
    vertex v;
    ThreadPool *q;
    int **m;
    int depth;
    int origin;
};
typedef struct bfsArgs bfsArgs;


void bfsArgsInit(bfsArgs *bfsArgs, Graph *graph, vertex v, ThreadPool *q, int **m, int origin) {
    bfsArgs->graph = graph;
    bfsArgs->v = v;
    bfsArgs->q = q;
    bfsArgs->m = m;
    //bfsArgs->depth = depth;
    bfsArgs->origin = origin;
}

void graphInit(graphArgs *graphArgs, Graph *graph, ThreadPool *q, int **m) {
    graphArgs->graph = graph;
    graphArgs->q = q;
    graphArgs->m = m;
}
/*
void *parallel_dfs_visit(void *args) {
    bfsArgs *data = (bfsArgs *) args;
    Graph *graph = data->graph;
    vertex v = data->v;
    ThreadPool *q = data->q;
    int **matrix = data->m;
    int depth = data->depth;
    int origin = data->origin;
    free(data);
    matrix[origin][v] = depth;
    node *neighborsPtr = graph->adjacencyLists[v];

    while (neighborsPtr != NULL) {
        vertex neighbor = neighborsPtr->v;

        pthread_mutex_lock(&graph->num_visits_mutexes[neighbor]);
        int neighborVisits = graph->num_visits[neighbor]++;
        int neighborDepth = matrix[origin][neighbor];
        pthread_mutex_unlock(&graph->num_visits_mutexes[neighbor]);

        if (neighborVisits == 0 || neighborDepth > depth + 1) {
            bfsArgs *params = malloc(sizeof(bfsArgs));
            bfsArgsInit(params, graph, neighbor, q, matrix, depth + 1, origin);
            TaskData td = {parallel_dfs_visit, params};

            insert(q->q2, td);
        }

        neighborsPtr = neighborsPtr->next;
    }

    --(q->runningThreads);
    return NULL;
}
*/

//Graph *graph, int **m, unsigned int origin
void *systematic_bfs2(void *args) {
    bfsArgs *data = (bfsArgs *) args;
    Graph *graph = data->graph;
    vertex v = data->v;
    ThreadPool *q = data->q;
    int **m = data->m;
    int origin = data->origin;
    free(data);

    int current = v;
    m[origin][origin] = 0;
    //lock?

    graph->num_visits[origin] = 1;

    node *nextNeighbor = graph->adjacencyLists[current];
    while (nextNeighbor) {
        pthread_mutex_lock(&graph->num_visits_mutexes[nextNeighbor->v]);
        if (!graph->num_visits[nextNeighbor->v]) {
            graph->num_visits[nextNeighbor->v]++;
            pthread_mutex_unlock(&graph->num_visits_mutexes[nextNeighbor->v]);

            m[origin][nextNeighbor->v] = m[origin][current] + 1;
            bfsArgs *params = malloc(sizeof(bfsArgs));
            bfsArgsInit(params, graph, nextNeighbor->v, q, m,origin);
            TaskData td = {systematic_bfs2, params};
            insert(q->q2, td);

        } else{
            pthread_mutex_unlock(&graph->num_visits_mutexes[nextNeighbor->v]);
        }

        nextNeighbor = nextNeighbor->next;
    }
    --(q->runningThreads);
    return NULL;
}

void parallel_bfs(Graph *graph, int **m, unsigned int origin) {
    bfsArgs *args;
    args = malloc(sizeof(bfsArgs));
    TaskQueue q;
    TaskQueue q2;
    initQueue(&q);
    initQueue(&q2);

    ThreadPool pool;
    pool.maxThreads = 4;
    pool.runningThreads = 0;
    pool.q = &q;
    pool.q2 = &q2;
    bfsArgsInit(args, graph, origin, &pool, m, origin);
    TaskData td = {systematic_bfs2, args};
    insert(pool.q, td);


    /* Start the tasks */
    runThreadPool(&pool);
}

//



void systematic_bfs(Graph *graph, int **m, unsigned int origin) {
    Queue *queue = malloc(sizeof(queue));
    init_Queue(queue);
    enqueue(queue, origin);
    int current;
    node *nextNeighbor;
    m[origin][origin] = 0;
    graph->num_visits[origin] = 1;
    while (!is_Empty(queue)) {
        dequeue(queue, &current);
        nextNeighbor = graph->adjacencyLists[current];
        while (nextNeighbor) {
            if (!graph->num_visits[nextNeighbor->v]++) {
                m[origin][nextNeighbor->v] = m[origin][current] + 1;
                graph->num_visits[nextNeighbor->v]++;
                enqueue(queue, nextNeighbor->v);
            }
            nextNeighbor = nextNeighbor->next;
        }
    }
}

void bfs(Graph *graph, int **m) {
    //printf("entered\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        for (int j = 0; j < graph->numVertices; ++j) {
            m[i][j] = -1;
        }
    }
    for (int i = 0; i < graph->numVertices; ++i) {
        for (int j = 0; j < graph->numVertices; ++j) {
            graph->num_visits[j] = 0;
        }
        //printf("entered %d\n",i);
        parallel_bfs(graph, m, i);
        //printf("left %d\n",i);
    }
    for (int i = 0; i < graph->numVertices; ++i) {
        m[i][i] = 0;
    }
    //printf("left\n");
}




/*
 * void parallel_bfs(Graph *graph, int **m, unsigned int origin) {
    int numVertices = graph->numVertices;
    bfsArgs *args;
    args = malloc(sizeof(bfsArgs));
    TaskQueue q;
    TaskQueue q2;
    initQueue(&q);
    initQueue(&q2);

    ThreadPool pool;
    pool.maxThreads = 4;
    pool.runningThreads = 0;
    pool.q = &q;
    pool.q2 = &q2;
    bfsArgsInit(args, graph, origin, &pool, m, 0, origin);
    TaskData td = {parallel_dfs_visit, args};
    insert(pool.q, td);


runThreadPool(&pool);

}
 */
/*

bfsArgs *data = (bfsArgs *) args;
Graph *graph = data->graph;
vertex v = data->v;
ThreadPool *q = data->q;
int **matrix = data->m;
int depth = data->depth;
int origin = data->origin;
free(data);
matrix[origin][v] = depth;


node *neighborsPtr = graph->adjacencyLists[v];

while (neighborsPtr != NULL) {
vertex neighbor = neighborsPtr->v;

pthread_mutex_lock(&graph->num_visits_mutexes[neighbor]);
int neighborVisits = graph->num_visits[neighbor]++;
int neighborDepth = matrix[origin][neighbor];
pthread_mutex_unlock(&graph->num_visits_mutexes[neighbor]);

if (neighborVisits == 0 || neighborDepth > depth + 1) {
bfsArgs *params = malloc(sizeof(bfsArgs));
bfsArgsInit(params, graph, neighbor, q, matrix, depth + 1, origin);
TaskData td = {parallel_dfs_visit, params};

insert(q->q2, td);
}

neighborsPtr = neighborsPtr->next;
}

--(q->runningThreads);
return NULL;
}
 */
