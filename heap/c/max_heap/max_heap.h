#ifndef _MAX_HEAP
#define _MAX_HEAP

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define REVERSE true
#define IN_ORDER false

typedef struct __max_heap max_heap;

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

typedef void (*__to_string_fn)(object object);
typedef __to_string_fn to_string_fn;

max_heap *new_max_heap(size_t heap_size, obj_type type, compare_obj_fn comparator);
size_t get_length(max_heap *heap);
void insert_obj(max_heap *heap, object object);
result remove_obj(max_heap *heap);
void show_heap(max_heap *heap, to_string_fn to_string, bool reverse);
void destroy_max_heap(max_heap *heap);

#endif
