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
    queue->q_size = 0;
    queue->data = calloc(queue->capacity, sizeof(*queue->data));
    assert(queue->data);
    queue->head = 0;
    queue->tail = 0;

    queue->dequeue = Queue_dequeue;
    queue->enqueue = Queue_enqueue;
    queue->free = Queue_free;
    queue->is_empty = Queue_is_empty;
    queue->iterate = Queue_iterate;
    queue->size = Queue_size;

  return queue;
}

void *Queue_dequeue(Queue *queue) { 
    CHECK_MEM(queue, error); 
    CHECK(queue->q_size != 0, error, "size can't be zero");

    void *item = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->q_size--;
    CHECK_MEM(item, error);
    return item;
error:
    return NULL;
}

void Queue_enqueue(Queue *queue, void *item) {
    assert(queue);
    assert(item);
    queue->data[queue->tail] = item;
    queue->q_size++;

    if (queue->q_size == queue->capacity) {
        size_t scale = 2;
        void **tmp = realloc(queue->data, scale * queue->capacity * sizeof(*tmp));
        assert(tmp);
        if (queue->head > queue->tail) {
            for (size_t i = queue->head; i < queue->capacity; ++i) {
                tmp[i + queue->capacity] = tmp[i];
                tmp[i] = NULL;
            }
            queue->head += queue->capacity;
        }
        queue->capacity *= scale;
        queue->data = tmp;
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
}

bool Queue_is_empty(const Queue *queue) {
    assert(queue);
    return queue->q_size == 0;
}

void Queue_iterate(const Queue *queue, void (*fn)(void *)) {
    assert(queue);
    assert(fn);
    
    if (queue->q_size == 0) {
        return;
    }
    for (size_t i = 0; i < queue->q_size; ++i) {
        void *x = queue->data[(i + queue->head) % queue->capacity];
        fn(x);
    }
}
size_t Queue_size(const Queue *queue) {
    assert(queue);
    return queue->q_size;

}
