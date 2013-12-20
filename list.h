
#include <stddef.h>
typedef struct list_node list_node_t;
typedef struct list      list_t;

struct list_node {
    list_node_t *next;
};

struct list {
    list_node_t *tail;
    list_node_t head;
};

void list_init(list_t *list);
int list_push(list_t *list, list_node_t *p);
list_node_t* list_pop(list_t *list);

#define list_pop_entry(list, type, member) ({                             \
        const typeof( ((type *)0)->member ) *__mptr = list_pop(list);     \
        (__mptr == NULL) ? NULL : ((type *)((char *)__mptr - offsetof(type, member)));})
