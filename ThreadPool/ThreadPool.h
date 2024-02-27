#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "TaskQueue.h"
#include <stdatomic.h>
#include <pthread.h>

struct ThreadPool {
    unsigned int maxThreads;
    atomic_int runningThreads;
    TaskQueue *q;
    TaskQueue *q2;
};

typedef struct ThreadPool ThreadPool;

void runThreadPool(ThreadPool *tp);

#endif
