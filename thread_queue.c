#include <string.h>
#include "queue.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM 20
#define N 100000

queue_t queue;
typedef struct Item {
    int value;
    node_t node;
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
        queue_push(&queue, &it->node);
    }
}

int main()
{
    int ret;
    int i;
    long sum = 0;
    pthread_t tid[NUM];
    queue_init(&queue);
    for (i = 0; i < NUM; i++) {
        ret = pthread_create(&tid[i], NULL, (void*)func, NULL);
    }

    for (i = 0; i < NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("exit\n");
    Item *it;
    for (i = 0; i < NUM * N; i++) {
        it = queue_pop_entry(&queue, Item, node);
        sum += it->value;
    }
    printf("sum:%ld\n", sum);
    return 0;
}
