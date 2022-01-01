#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __linked_list linked_list;

typedef void (*__to_string_fn)(void *object);
typedef __to_string_fn to_string_fn;

linked_list *new_linked_list(size_t element_size);
size_t get_length(linked_list *list);
bool is_empty(linked_list *list);
void insert_first(linked_list *list, void *object);
void insert_last(linked_list *list, void *object);
void remove_first(linked_list *list, void *buffer);
void remove_last(linked_list *list, void *buffer);
void insert_obj_at(linked_list *list, void *object, int index);
void *get_obj_at(linked_list *list, int index);
void remove_obj_at(linked_list *list, int index, void *buffer);
void show_list(linked_list *list, to_string_fn to_string, bool reverse);
void destroy_linked_list(linked_list *list);

#endif
