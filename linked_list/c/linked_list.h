#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

typedef struct __linked_list linked_list;

linked_list *new_linked_list(int type);
size_t get_length(linked_list *list);
bool is_empty(linked_list *list);
void insert_first(linked_list *list, struct object object);
void insert_last(linked_list *list, struct object object);
void remove_first(linked_list *list);
void remove_last(linked_list *list);
void insert_obj_at(linked_list *list, struct object object, int index);
void *get_obj_at(linked_list *list, int index);
void remove_obj_at(linked_list *list, int index);
void destroy_linked_list(linked_list *list);

#endif
