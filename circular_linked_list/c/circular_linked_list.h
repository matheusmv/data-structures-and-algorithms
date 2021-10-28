#ifndef _CIRCULAR_LINKED_LIST
#define _CIRCULAR_LINKED_LIST

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __circular_linked_list circular_linked_list;

circular_linked_list *new_circular_linked_list(int type);
size_t get_length(circular_linked_list *list);
bool is_empty(circular_linked_list *list);
void insert_obj(circular_linked_list *list, struct object object);
void remove_obj(circular_linked_list *list);
void insert_obj_at(circular_linked_list *list, struct object object, int index);
void *get_obj_at(circular_linked_list *list, int index);
void remove_obj_at(circular_linked_list *list, int index);
void show_list(circular_linked_list *list, void (*to_string)(struct object object), bool reverse);
void destroy_circular_linked_list(circular_linked_list *list);

#endif
