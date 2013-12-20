all: test_queue test_list

test_queue: queue.c test_queue.c
	gcc -g -Wall -o $@ $^

test_list: list.c test_list.c
	gcc -g -Wall -o $@ $^

clean:
	rm queue
