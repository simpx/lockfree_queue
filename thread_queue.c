#include <string.h>
#include "queue.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

queue_t queue;
typedef struct Item {
    int value;
    node_t node;
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
        queue_push(&queue, &it->node);
    }
}

int main()
{
    int ret;
    pthread_t tid1, tid2, tid3;
    queue_init(&queue);
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
        it = queue_pop_entry(&queue, Item, node);
        sum += it->value;
    }
    printf("sum:%d\n", sum);
    return 0;
}
