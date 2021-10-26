#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

struct object {
        int number;
        char *state;
        char *abbreviation;
};

typedef struct __array_list array_list;

array_list *new_array_list(size_t array_size);
size_t get_size(array_list *array);
size_t get_length(array_list *array);
void append_obj(array_list *array, struct object new_object);
void remove_obj(array_list *array);
void add_obj_at(array_list *array, struct object new_object, int index);
struct object get_obj_at(array_list *array, int index);
void remove_obj_at(array_list *array, int index);
void destroy_array_list(array_list *array);

#endif
