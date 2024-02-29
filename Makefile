CC = gcc
CFLAGS = -pthread

SRCS = main.c code.c SyncGraph/graph.c ThreadPool/ThreadPool.c ThreadPool/TaskQueue.c Queue/Queue.c
OBJS = $(SRCS:.c=.o)

part_III.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o part_III.out

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
