#include <string.h>
#include "list.h"
#include <stdio.h>

typedef struct Item {
    int value;
    list_node_t node;
}Item;

int main()
{
    list_t list;
    list_init(&list);

    Item it1;
    memset(&it1, 0, sizeof(Item));
    it1.value = 1;
    list_push(&list, &it1.node);


    Item it2;
    memset(&it2, 0, sizeof(Item));
    it2.value = 2;
    list_push(&list, &it2.node);

    Item it3;
    memset(&it3, 0, sizeof(Item));
    it3.value = 3;
    list_push(&list, &it3.node);

    Item *it;
    printf("%d\n", (it = list_pop_entry(&list, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = list_pop_entry(&list, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = list_pop_entry(&list, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = list_pop_entry(&list, Item, node)) == NULL ? -1: it->value);
    printf("%d\n", (it = list_pop_entry(&list, Item, node)) == NULL ? -1: it->value);

    return 0;
}
