#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

typedef struct Queue {
    size_t capacity, q_size;
    void **data;
    size_t head, tail;

    void (*free)(struct Queue *queue);

    void *(*dequeue)(struct Queue *queue);
    void (*enqueue)(struct Queue *queue, void *item);

    bool (*is_empty)(const struct Queue *queue);
    void (*iterate)(const struct Queue *queue, void (*fn)(void *));
    size_t (*size)(const struct Queue *queue);
} Queue;

void Queue_free(Queue *queue);
Queue *Queue_init(void);

void *Queue_dequeue(Queue *queue);
void Queue_enqueue(Queue *queue, void *item);

bool Queue_is_empty(const Queue *queue);
void Queue_iterate(const Queue *queue, void (*fn)(void *));
size_t Queue_size(const Queue *queue);

#endif
