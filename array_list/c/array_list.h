#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GETSTDERROR() (strerror(errno))

#define REVERSE true
#define IN_ORDER false

typedef struct __array_list array_list;

typedef void (*__to_string_fn)(void *object);
typedef __to_string_fn to_string_fn;

array_list *new_array_list(size_t array_size, size_t element_size);
size_t get_length(array_list *array);
void append_obj(array_list *array, void *object);
int remove_obj(array_list *array, void *buffer);
void add_obj_at(array_list *array, void *object, int index);
int get_obj_at(array_list *array, int index, void *buffer);
int remove_obj_at(array_list *array, int index, void *buffer);
void show_array(array_list *array, to_string_fn to_string, bool reverse);
void destroy_array_list(array_list *array);

#endif
