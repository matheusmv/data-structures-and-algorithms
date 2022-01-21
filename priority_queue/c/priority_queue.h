#ifndef _PRIORITY_QUEUE
#define _PRIORITY_QUEUE

#include <stdbool.h>
#include <stdlib.h>

#define IN_ORDER false
#define REVERSE true

typedef struct priority_queue priority_queue;

typedef int (*compare_obj_fn)(void *a, void *b);
typedef void (*to_string_fn)(void *object);

priority_queue *priority_queue_create(size_t size, size_t element_size, compare_obj_fn comparator);
size_t priority_queue_length(priority_queue *queue);
void priority_queue_enqueue(priority_queue *queue, void *object);
int priority_queue_dequeue(priority_queue *queue, void *buffer);
void *priority_queue_peek(priority_queue *queue);
void priority_queue_show(priority_queue *queue, to_string_fn to_string, bool reverse);
void priority_queue_free(priority_queue *queue);

#endif
