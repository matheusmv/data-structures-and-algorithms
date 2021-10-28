#include "circular_linked_list.h"

typedef struct __node {
        struct object value;
        struct __node *next;
} node;

typedef struct __circular_linked_list {
        int type;
        size_t length;
        struct __node *head;
} circular_linked_list;

static void increase_list_length(circular_linked_list *list)
{
        list->length += 1;
}

static void decrease_list_length(circular_linked_list *list)
{
        const size_t list_length = list->length;

        if (list_length > 0)
                list->length -= 1;
}

static node *get_node(circular_linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_circular_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                node *node = list->head;

                for (int i = 0; i < index; i++)
                        node = node->next;

                return node;
        }

        return NULL;
}

circular_linked_list *new_circular_linked_list(int type)
{
        circular_linked_list *list = malloc(sizeof(circular_linked_list));

        if (list == NULL)
                return NULL;

        const int list_type = get_object_type(type);

        *list = (circular_linked_list) {
                .type = list_type,
                .length = 0,
                .head = NULL,
        };

        return list;
}

size_t get_length(circular_linked_list *list)
{
        return list->length;
}

bool is_empty(circular_linked_list *list)
{
        return list->head == NULL;
}

void insert_obj(circular_linked_list *list, struct object object)
{
        if (list != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *head = list->head;

                        *new_node = (node) {
                                .next = head,
                                .value = object,
                        };

                        list->head = new_node;

                        increase_list_length(list);
                }
        }
}

void remove_obj(circular_linked_list *list)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                node *head = NULL;

                if (get_length(list) == 1) {
                        head = list->head;
                        list->head = NULL;
                } else {
                        node *previous = get_node(list, list_end - 1);
                        head = previous->next;
                        previous->next = head->next;
                }

                decrease_list_length(list);
                free(head);
        }
}

void insert_obj_at(circular_linked_list *list, struct object object, int index)
{
        if (list != NULL) {
                const size_t list_length = list->length;

                if (index > list_length || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_circular_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        insert_obj(list, object);
                } else {
                        node *previous = get_node(list, index - 1);
                        node *current = previous->next;

                        node *new_node = malloc(sizeof(node));

                        if (new_node != NULL) {
                                *new_node = (node) {
                                        .next = current,
                                        .value = object,
                                };

                                previous->next = new_node;

                                increase_list_length(list);
                        }
                }
        }
}

void *get_obj_at(circular_linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;
                const int list_type = list->type;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_circular_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                node *node = get_node(list, index);

                return get_object(&node->value, list_type);
        }

        return NULL;
}

void remove_obj_at(circular_linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_circular_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        remove_obj(list);
                } else {
                        node *previous = get_node(list, index - 1);
                        node *current = previous->next;
                        node *next = current->next;

                        previous->next = next;

                        free(current);
                        decrease_list_length(list);
                }
        }
}

void show_list(circular_linked_list *list, void (*to_string)(struct object object), bool reverse)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;

                int start = reverse ? list_length : 0;
                int end = reverse ? 0 : list_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(*(struct object *) get_obj_at(list, i));
                } else {
                        for (int i = start; i < end; i++)
                                to_string(*(struct object *) get_obj_at(list, i));
                }
        }
}

void destroy_circular_linked_list(circular_linked_list *list)
{
        if (list != NULL) {
                node *node;

                while (!is_empty(list) && get_length(list) > 0) {
                        node = list->head;
                        list->head = node->next;
                        free(node);
                        decrease_list_length(list);
                }

                list->type = -1;
                list->length = -1;
                list->head = NULL;

                free(list);
                list = NULL;
        }
}
