
CC = gcc
CFLAGS = -std=c11 -g  -pthread

SRCS-C = BFS.c main.c ./SyncGraph/graph.c
OBJS = $(SRCS-C:.c=.o) 

all: slowBFS.out

slowBFS.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o slowBFS.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) slowBFS.out