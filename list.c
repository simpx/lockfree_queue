#include "list.h"


void list_init(list_t *list)
{
    list->head.next = NULL;
    list->tail = &list->head;
}

int list_push(list_t *list, list_node_t *p)
{
    list->tail->next = p;
    list->tail = p;
    return 0;
}

list_node_t* list_pop(list_t *list)
{
    list_node_t *p = list->head.next;
    if (p != NULL) {
        list->head.next = p->next;
    }
    return p;
}

