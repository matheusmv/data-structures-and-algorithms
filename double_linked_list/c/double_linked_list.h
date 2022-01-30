#ifndef _DOUBLE_LINKED_LIST
#define _DOUBLE_LINKED_LIST

#include <stdbool.h>
#include <stdlib.h>

#define IN_ORDER false
#define REVERSE  true

typedef struct double_linked_list double_linked_list;

typedef void (*to_string_fn)(void *object);

double_linked_list *double_linked_list_create(size_t element_size);
size_t double_linked_list_length(double_linked_list *list);
bool double_linked_list_is_empty(double_linked_list *list);
void double_linked_list_insert_first(double_linked_list *list, void *object);
void double_linked_list_insert_last(double_linked_list *list, void *object);
void double_linked_list_remove_first(double_linked_list *list, void *buffer);
void double_linked_list_remove_last(double_linked_list *list, void *buffer);
void double_linked_list_insert_obj_at(double_linked_list *list, void *object, size_t index);
void *double_linked_list_get_obj_at(double_linked_list *list, size_t index);
void double_linked_list_remove_obj_at(double_linked_list *list, size_t index, void *buffer);
void double_linked_list_show(double_linked_list *list, to_string_fn to_string, bool reverse);
void double_linked_list_free(double_linked_list **list);

#endif
