#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include "data_types.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define REVERSE true
#define IN_ORDER false

typedef struct __array_list array_list;

typedef void (*__to_string_fn)(object object);
typedef __to_string_fn to_string_fn;

array_list *new_array_list(size_t array_size, obj_type type);
size_t get_length(array_list *array);
void append_obj(array_list *array, object new_object);
result remove_obj(array_list *array);
void add_obj_at(array_list *array, object new_object, int index);
result get_obj_at(array_list *array, int index);
result remove_obj_at(array_list *array, int index);
void show_array(array_list *array, to_string_fn to_string, bool reverse);
void destroy_array_list(array_list *array);

#endif
