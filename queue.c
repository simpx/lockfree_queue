#include "queue.h"

void queue_init(queue_t *queue)
{
    queue->head.next = NULL;
    queue->tail = &queue->head;
}

int queue_push(queue_t *queue, node_t *p)
{
    node_t *tail;
    do {
        tail = queue->tail;
    } while (__sync_bool_compare_and_swap(&tail->next, NULL, p) == 0);

    __sync_bool_compare_and_swap(&queue->tail, tail, p);
    return 0;
}

node_t* queue_pop(queue_t *queue)
{
    //似乎aba问题在出队列的时候没什么影响
    //我只关心出去的是不是一个正确的结构体，会不会造成core
    node_t *p;
    do {
        if((p = queue->head.next) == NULL)
            return NULL;
    } while (__sync_bool_compare_and_swap(&queue->head.next, p, p->next) == 0);
    return p;
}

