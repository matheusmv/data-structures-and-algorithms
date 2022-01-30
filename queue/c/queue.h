#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

#define IN_ORDER false
#define REVERSE  true

typedef struct queue queue;

typedef void (*to_string_fn)(void *object);

queue *queue_new(size_t element_size);
size_t queue_length(queue *queue);
bool queue_is_empty(queue *queue);
void queue_enqueue(queue *queue, void *object);
void queue_dequeue(queue *queue, void *buffer);
void *queue_peek(queue *queue);
void queue_show(queue *queue, to_string_fn to_string, bool reverse);
void queue_free(queue **queue);

#endif
