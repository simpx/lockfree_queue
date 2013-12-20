#ifndef EASY_QUEUE_H_
#define EASY_QUEUE_H_

#include <stddef.h>

typedef struct lockfree_queue_node node_t;
typedef struct lockfree_queue      queue_t;

struct lockfree_queue_node {
    node_t   *next;
};

struct lockfree_queue {
    node_t   *tail;
    node_t    head;
};

void queue_init(queue_t *queue);
int queue_push(queue_t *queue, node_t *p);
node_t* queue_pop(queue_t *queue);

#define queue_pop_entry(queue, type, member) ({                             \
        const typeof( ((type *)0)->member ) *__mptr = queue_pop(queue);     \
        (__mptr == NULL) ? NULL : ((type *)((char *)__mptr - offsetof(type, member)));})


#endif
