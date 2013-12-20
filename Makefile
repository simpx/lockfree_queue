all: test_queue test_list thread_list thread_queue

test_queue: queue.c test_queue.c
	gcc -g -Wall -o $@ $^

test_list: list.c test_list.c
	gcc -g -Wall -o $@ $^

thread_queue: queue.c thread_queue.c
	gcc -g -Wall -lpthread -o $@ $^

thread_list: list.c thread_list.c
	gcc -g -Wall -lpthread -leasy -lm -o $@ $^

clean:
	rm queue
