#ifndef _DOUBLE_LINKED_LIST
#define _DOUBLE_LINKED_LIST

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __double_linked_list double_linked_list;

double_linked_list *new_double_linked_list(int type);
size_t get_length(double_linked_list *list);
bool is_empty(double_linked_list *list);
void insert_first(double_linked_list *list, struct object object);
void insert_last(double_linked_list *list, struct object object);
void remove_first(double_linked_list *list);
void remove_last(double_linked_list *list);
void insert_obj_at(double_linked_list *list, struct object object, int index);
void *get_obj_at(double_linked_list *list, int index);
void remove_obj_at(double_linked_list *list, int index);
void show_list(double_linked_list *list, void (*to_string)(struct object object), bool reverse);
void destroy_double_linked_list(double_linked_list *list);

#endif
