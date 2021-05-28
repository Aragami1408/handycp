#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
  size_t capacity, size;
  void **data;
  size_t head, tail;
} Queue;

void Queue_free(Queue *queue);
Queue *Queue_init(void);

void *Queue_dequeue(Queue *queue);
void Queue_enqueue(Queue *queue, void *item);

bool Queue_is_empty(const Queue *queue);
void Queue_iterate(const Queue *queue, void (*fn)(void *));
size_t Queue_size(const Queue *queue);

#endif
