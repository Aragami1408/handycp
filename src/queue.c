#include "queue.h"

void Queue_free(Queue *queue) {
  assert(queue);
  free(queue->data);
  free(queue);
}
Queue *Queue_init(void) {
  Queue *queue = calloc(1, sizeof(*queue));
  assert(queue);
  queue->capacity = 100;
  queue->size = 0;
  queue->data = calloc(queue->capacity, sizeof(*queue->data));
  assert(queue->data);
  queue->head = 0;
  queue->tail = 0;

  return queue;
}

void *Queue_dequeue(Queue *queue) { assert(queue); }
void Queue_enqueue(Queue *queue, void *item) {}

bool Queue_is_empty(const Queue *queue) {}
void Queue_iterate(const Queue *queue, void (*fn)(void *)) {}
size_t Queue_size(const Queue *queue) {}
