all: queue

queue: queue.c
	gcc -g -Wall -o $@ $^

clean:
	rm queue
