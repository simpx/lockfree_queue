#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct lockfree_queue_node node_t;
typedef struct lockfree_queue      queue_t;

struct lockfree_queue_node {
    int      *value;
    node_t   *next;
};

struct lockfree_queue {
    node_t   *tail;
    node_t    head;
};

int en_queue(queue_t *queue, int *value)
{
    node_t *tail;
    node_t *p = (node_t *)malloc(sizeof(node_t));
    memset(p, 0, sizeof(node_t));
    p->value = value;
    p->next = NULL;
    do {
        tail = queue->tail;
    } while (__sync_bool_compare_and_swap(&tail->next, NULL, p) == 0);

    __sync_bool_compare_and_swap(&queue->tail, tail, p);
    return 0;
}

/*
int de_queue(queue_t *queue)
{
    node_t *p;
    do {

    }
}
*/

int de_queue(queue_t *queue)
{
    node_t *p;
    do {
        if((p = queue->head.next) == NULL)
            return -1;
    } while (__sync_bool_compare_and_swap(&queue->head.next, p, p->next) == 0);
    //似乎aba问题在出队列的时候没什么影响
    //我只关心出去的是不是一个正确的结构体，会不会造成core
    return *p->value;
}

void print_queue(queue_t *queue)
{
    node_t *p = queue->head.next;
    while (p != NULL) {
        printf("%d\n", *p->value);
        p = p->next;
    }
}

int main()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    memset(queue, 0, sizeof(queue_t));
    queue->tail = &queue->head;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    en_queue(queue, &a);
    en_queue(queue, &b);
    en_queue(queue, &c);
    en_queue(queue, &d);
    print_queue(queue);
    printf("-----------\n");
    printf("%d\n", de_queue(queue));
    printf("%d\n", de_queue(queue));
    printf("%d\n", de_queue(queue));
    printf("%d\n", de_queue(queue));
    printf("%d\n", de_queue(queue));
    
    return 0;
}
