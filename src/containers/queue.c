#include "dsalib/containers/queue.h"
#include <stdio.h>

void dsalib_queue_init(dsalib_queue_t *q){
    q->front = 0;
    q->tail = 0;
}

int dsalib_queue_is_empty(dsalib_queue_t *q){
    return q->front == q->tail;
}

int dsalib_queue_is_full(dsalib_queue_t *q){
    return (q->tail + 1) % MAX_SIZE == q->front;
}

void dsalib_queue_enqueue(dsalib_queue_t *q, int value){
    if (dsalib_queue_is_full(q))
    {
        printf("Queue overflow!\n");
        return;
    }
    q->item[q->tail] = value;
    q->tail = (q->tail + 1) % MAX_SIZE;

}

int dsalib_queue_dequeue(dsalib_queue_t *q){
    if(dsalib_queue_is_empty(q)){
        printf("Queue underflow!\n");
        return -1;
    }
    int value = q->item[q->front];
    q->front = (q-> front + 1) % MAX_SIZE;
    return value;
}

int dsalib_queue_peek(dsalib_queue_t *q){
    if(dsalib_queue_is_empty(q)){
        printf("Queue empty!\n");
        return -1;
    }
    return q->item[q->front];
}

int dsalib_queue_size(dsalib_queue_t *q){
    if(q->tail >= q->front){
        return q->tail - q->front;
    }
    return (q->tail - q->front + MAX_SIZE) % MAX_SIZE;
}
