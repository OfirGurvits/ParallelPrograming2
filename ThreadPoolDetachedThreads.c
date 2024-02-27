#include "ThreadPool.h"
#include "TaskQueue.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
// right now thread pool doesn't re-use threads, always creates new threads
void runThreadPool(ThreadPool *tp) {
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
    /* As long as there are tasks in the queue or running threads... */
    while (!isEmpty(tp->q) || tp->runningThreads > 0) { // the threadPool isn't empty and there are threads that have been created
        /* If we are not past max number of threads */
        if (!isEmpty(tp->q)  && tp->runningThreads < tp->maxThreads) { // only if there is an available threads
            /* Run task */
            TaskData data = pop(tp->q);

            pthread_t thread;
            if (pthread_create(&thread, &tattr, data.function, data.args)) {
                perror("pthread_create failed.");
                exit(1);
            } else {
                ++(tp->runningThreads); // created a thread, add +1 to number of running threads
            }
        }
    } // busy waiting, no tasks or no available threads do busy waiting for getting more tasks/ threads to be available
}