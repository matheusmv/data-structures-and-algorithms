#ifndef _QUEUE
#define _QUEUE

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __queue queue;

queue *new_queue(size_t element_size);
size_t get_length(queue *queue);
bool is_empty(queue *queue);
void enqueue(queue *queue, void *object);
void dequeue(queue *queue);
void *peek(queue *queue);
void show_queue(queue *queue, void (*to_string)(void *object), bool reverse);
void destroy_queue(queue *queue);

#endif
