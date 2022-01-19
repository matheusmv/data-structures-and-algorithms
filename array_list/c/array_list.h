#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define REVERSE true
#define IN_ORDER false

typedef struct array_list array_list;

typedef void (*to_string_fn)(void *object);

array_list *array_list_create(size_t array_size, size_t element_size);
size_t array_list_length(array_list *array);
void array_list_append(array_list *array, void *object);
void array_list_append_at(array_list *array, void *object, int index);
int array_list_remove(array_list *array, void *buffer);
int array_list_find_at(array_list *array, int index, void *buffer);
int array_list_remove_at(array_list *array, int index, void *buffer);
void array_list_show(array_list *array, to_string_fn to_string, bool reverse);
void array_list_free(array_list *array);

#endif
