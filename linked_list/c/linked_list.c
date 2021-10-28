#include "linked_list.h"

typedef struct __node {
        struct object value;
        struct __node *next;
} node;

typedef struct __linked_list {
        int type;
        size_t length;
        struct __node *head;
        struct __node *tail;
} linked_list;

static void increase_list_length(linked_list *list)
{
        list->length += 1;
}

static void decrease_list_length(linked_list *list)
{
        const size_t list_length = list->length;

        if (list_length > 0)
                list->length -= 1;
}

static node *get_node(linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                node *node = list->head;

                for (int i = 0; i < index; i++)
                        node = node->next;

                return node;
        }

        return NULL;
}

linked_list *new_linked_list(int type)
{
        linked_list *list = malloc(sizeof(linked_list));

        if (list == NULL)
                return NULL;

        const int list_type = get_object_type(type);

        *list = (linked_list) {
                .type = list_type,
                .length = 0,
                .head = NULL,
                .tail = NULL,
        };

        return list;
}

size_t get_length(linked_list *list)
{
        return list->length;
}

bool is_empty(linked_list *list)
{
        return list->head == NULL;
}

void insert_first(linked_list *list, struct object object)
{
        if (list != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *head = list->head;

                        *new_node = (node) {
                                .next = head,
                                .value = object,
                        };

                        if (list->tail == NULL)
                                list->tail = new_node;

                        list->head = new_node;

                        increase_list_length(list);
                }
        }
}

void insert_last(linked_list *list, struct object object)
{
        if (list != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *tail = list->tail;

                        if (!is_empty(list))
                                tail->next = new_node;

                        *new_node = (node) {
                                .next = NULL,
                                .value = object,
                        };

                        if (list->head == NULL)
                                list->head = new_node;

                        list->tail = new_node;

                        increase_list_length(list);
                }
        }
}

void remove_first(linked_list *list)
{
        if (!is_empty(list)) {
                node *head = list->head;

                if (get_length(list) == 1) {
                        list->head = NULL;
                        list->tail = NULL;
                } else {
                        list->head = head->next;
                }

                decrease_list_length(list);
                free(head);
        }
}

void remove_last(linked_list *list)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                node *tail = NULL;

                if (get_length(list) == 1) {
                        tail = list->head;

                        list->head = NULL;
                        list->tail = NULL;
                } else {
                        node *previous = get_node(list, list_end - 1);

                        tail = previous->next;
                        previous->next = NULL;
                }

                decrease_list_length(list);
                free(tail);
        }
}

void insert_obj_at(linked_list *list, struct object object, int index)
{
        if (list != NULL) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_length || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        insert_first(list, object);
                } else if (index == list_end) {
                        insert_last(list, object);
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

                                if (list->tail == NULL)
                                        list->tail = new_node;

                                increase_list_length(list);
                        }
                }
        }
}

void *get_obj_at(linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;
                const int list_type = list->type;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                node *node = get_node(list, index);

                return get_object(&node->value, list_type);
        }

        return NULL;
}

void remove_obj_at(linked_list *list, int index)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_linked_list(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        remove_first(list);
                } else if (index == list_end) {
                        remove_last(list);
                } else {
                        node *previous = get_node(list, index - 1);
                        node *current = previous->next;

                        previous->next = current->next;

                        free(current);
                        decrease_list_length(list);
                }
        }
}

void show_list(linked_list *list, void (*to_string)(struct object object), bool reverse)
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

void destroy_linked_list(linked_list *list)
{
        if (list != NULL) {
                node *node;

                while (!is_empty(list)) {
                        node = list->head;
                        list->head = node->next;
                        free(node);
                }

                list->type = -1;
                list->length = -1;
                list->head = NULL;
                list->tail = NULL;

                free(list);
                list = NULL;
        }
}
