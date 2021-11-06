#ifndef _PRIORITY_QUEUE
#define _PRIORITY_QUEUE

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __priority_queue priority_queue;

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

typedef void (*__to_string_fn)(object object);
typedef __to_string_fn to_string_fn;

priority_queue *new_priority_queue(size_t size, obj_type type, compare_obj_fn comparator);
size_t get_length(priority_queue *queue);
void enqueue(priority_queue *queue, object object);
result dequeue(priority_queue *queue);
result peek(priority_queue *queue);
void show_priority_queue(priority_queue *queue, to_string_fn to_string, bool reverse);
void destroy_priority_queue(priority_queue *queue);

#endif
