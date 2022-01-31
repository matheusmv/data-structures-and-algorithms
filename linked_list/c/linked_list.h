#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stdbool.h>
#include <stdlib.h>

#define IN_ORDER false
#define REVERSE true

typedef struct linked_list linked_list;

typedef void (*to_string_fn)(void *object);

linked_list *linked_list_create(size_t element_size);
size_t linked_list_length(linked_list *list);
bool linked_list_is_empty(linked_list *list);
void linked_list_insert_first(linked_list *list, void *object);
void linked_list_insert_last(linked_list *list, void *object);
void linked_list_remove_first(linked_list *list, void *buffer);
void linked_list_remove_last(linked_list *list, void *buffer);
void linked_list_insert_obj_at(linked_list *list, void *object, size_t index);
void *linked_list_get_obj_at(linked_list *list, size_t index);
void linked_list_remove_obj_at(linked_list *list, size_t index, void *buffer);
void linked_list_show(linked_list *list, to_string_fn to_string, bool reverse);
void linked_list_free(linked_list **list);

#endif
