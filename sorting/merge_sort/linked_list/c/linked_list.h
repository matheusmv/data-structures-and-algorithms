#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define REVERSE true
#define IN_ORDER false

typedef struct __linked_list linked_list;

typedef void (*__to_string_fn)(object object);
typedef __to_string_fn to_string_fn;

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

linked_list *new_linked_list(int type);
size_t get_length(linked_list *list);
bool is_empty(linked_list *list);
void insert_first(linked_list *list, object object);
void insert_last(linked_list *list, object object);
result remove_first(linked_list *list);
result remove_last(linked_list *list);
void insert_obj_at(linked_list *list, object object, int index);
result get_obj_at(linked_list *list, int index);
result remove_obj_at(linked_list *list, int index);
void show_list(linked_list *list, to_string_fn to_string, bool reverse);
void m_sort_list(linked_list *list, compare_obj_fn comparator);
void destroy_linked_list(linked_list *list);

#endif
