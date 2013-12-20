#include <string.h>
#include "queue.h"
#include <stdio.h>

typedef struct Item {
    int value;
    node_t node;
}Item;

int main()
{
    queue_t queue;
    queue_init(&queue);

    Item it1;
    memset(&it1, 0, sizeof(Item));
    it1.value = 1;
    queue_push(&queue, &it1.node);


    Item it2;
    memset(&it2, 0, sizeof(Item));
    it2.value = 2;
    queue_push(&queue, &it2.node);

    Item it3;
    memset(&it3, 0, sizeof(Item));
    it3.value = 3;
    queue_push(&queue, &it3.node);

    Item *it;
    printf("%d\n", (it = queue_pop_entry(&queue, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = queue_pop_entry(&queue, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = queue_pop_entry(&queue, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = queue_pop_entry(&queue, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = queue_pop_entry(&queue, Item, node)) == NULL ? -1: it->value);

    return 0;
}
