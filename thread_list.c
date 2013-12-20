#include <string.h>
#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <easy/easy_atomic.h>

easy_atomic_t lock;
list_t list;
typedef struct Item {
    int value;
    list_node_t node;
}Item;

void func(void *args)
{
    Item *it;
    int i;
    for (i = 0; i < 100000; i++)
    {
        it = (Item *)malloc(sizeof(Item));
        memset(it, 0, sizeof(Item));
        it->value = i;
        easy_spin_lock(&lock);
        list_push(&list, &it->node);
        easy_spin_unlock(&lock);
    }
}

int main()
{
    lock = 0;
    int ret;
    pthread_t tid1, tid2, tid3;
    list_init(&list);
    ret = pthread_create(&tid1, NULL, (void*)func, NULL);
    ret = pthread_create(&tid2, NULL, (void*)func, NULL);
    ret = pthread_create(&tid3, NULL, (void*)func, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    printf("exit\n");
    int i;
    int sum = 0;
    Item *it;
    for (i = 0; i < 300000; i++) {
        it = list_pop_entry(&list, Item, node);
        sum += it->value;
    }
    printf("sum:%d\n", sum);
    return 0;
}
