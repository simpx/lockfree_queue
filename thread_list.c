#include <string.h>
#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <easy/easy_atomic.h>

#define NUM 20
#define N 100000

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
    for (i = 0; i < N; i++)
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
    int i;
    long sum = 0;
    pthread_t tid[NUM];
    list_init(&list);
    for (i = 0; i < NUM; i++) {
        ret = pthread_create(&tid[i], NULL, (void*)func, NULL);
    }

    for (i = 0; i < NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("exit\n");
    Item *it;
    for (i = 0; i < NUM * N; i++) {
        it = list_pop_entry(&list, Item, node);
        sum += it->value;
    }
    printf("sum:%ld\n", sum);
    return 0;
}
