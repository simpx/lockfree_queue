#include <string.h>
#include "queue.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define CONSUMER_NUM 2
#define PRODUCER_NUM 1
#define N 20000

int stop;
queue_t queue;
typedef struct Item {
    int value;
    node_t node;
}Item;

void consumer(void *args)
{
    Item *it;
    int i = 0;
    while (stop == 0)
    {
        if ((it = queue_pop_entry(&queue, Item, node)) != NULL)
        {
            i++;
            if (it->value == N - 1) {
                stop = 1;
                break;
            }
        }
    }
    printf("consume %d items\n", i);
}

void producer(void *args)
{
    Item *it;
    int i;
    for (i = 0; i < N / PRODUCER_NUM; i++)
    {
        it = (Item *)malloc(sizeof(Item));
        memset(it, 0, sizeof(Item));
        it->value = i;
        queue_push(&queue, &it->node);
    }
    printf("produce %d items\n", i);
}

int main()
{
    int ret;
    int i;
    stop = 0;
    pthread_t tid[CONSUMER_NUM + PRODUCER_NUM];
    queue_init(&queue);

    for (i = 0; i < PRODUCER_NUM; i++) {
        ret = pthread_create(&tid[i], NULL, (void*)producer, NULL);
    }


    for (i = PRODUCER_NUM; i < CONSUMER_NUM + PRODUCER_NUM; i++) {
        ret = pthread_create(&tid[i], NULL, (void*)consumer, NULL);
    }

    for (i = 0; i < PRODUCER_NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("producer exit\n");

    for (i = PRODUCER_NUM; i < CONSUMER_NUM + PRODUCER_NUM; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("exit\n");
    return 0;
}
