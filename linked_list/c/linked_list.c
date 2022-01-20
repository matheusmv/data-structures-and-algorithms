#include "linked_list.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef struct node node;
struct node {
        void *value;
        node *next;
};

typedef struct linked_list linked_list;
struct linked_list {
        size_t esize;
        size_t length;
        node *head;
        node *tail;
};

#define GETSTDERROR() (strerror(errno))

static void
increase_list_length(linked_list *list)
{
        list->length += 1;
}

static void
decrease_list_length(linked_list *list)
{
        const size_t list_length = list->length;

        if (list_length > 0)
                list->length -= 1;
}

static node *
get_node(linked_list *list, int index)
{
        if (!linked_list_is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        linked_list_free(list);
                        exit(EXIT_FAILURE);
                }

                node *node = list->head;

                for (int i = 0; i < index; i++)
                        node = node->next;

                return node;
        }

        return NULL;
}

static void *
copy_object(const void *obj, size_t obj_size)
{
        void *copy;

        copy = malloc(obj_size);

        memcpy(copy, obj, obj_size);

        return copy;
}

linked_list *
linked_list_create(size_t element_size)
{
        if (element_size == 0)
                return NULL;

        linked_list *list = malloc(sizeof(linked_list));

        if (list == NULL)
                return NULL;

        *list = (linked_list) {
                .esize = element_size,
                .length = 0,
                .head = NULL,
                .tail = NULL,
        };

        return list;
}

size_t
linked_list_length(linked_list *list)
{
        return list->length;
}

bool
linked_list_is_empty(linked_list *list)
{
        return list->head == NULL;
}

void
linked_list_insert_first(linked_list *list, void *object)
{
        if (list != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *head = list->head;

                        *new_node = (node) {
                                .next = head,
                                .value = copy_object(object, list->esize),
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                free(new_node);
                                linked_list_free(list);
                                exit(EXIT_FAILURE);
                        }

                        if (list->tail == NULL)
                                list->tail = new_node;

                        list->head = new_node;

                        increase_list_length(list);
                }
        }
}

void
linked_list_insert_last(linked_list *list, void *object)
{
        if (list != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *tail = list->tail;

                        if (!linked_list_is_empty(list))
                                tail->next = new_node;

                        *new_node = (node) {
                                .next = NULL,
                                .value = copy_object(object, list->esize),
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                free(new_node);
                                linked_list_free(list);
                                exit(EXIT_FAILURE);
                        }

                        if (list->head == NULL)
                                list->head = new_node;

                        list->tail = new_node;

                        increase_list_length(list);
                }
        }
}

void
linked_list_remove_first(linked_list *list, void *buffer)
{
        if (!linked_list_is_empty(list)) {
                node *head = list->head;

                if (linked_list_length(list) == 1) {
                        list->head = NULL;
                        list->tail = NULL;
                } else {
                        list->head = head->next;
                }

                if (buffer != NULL && head != NULL)
                        memmove(buffer, head->value, list->esize);

                decrease_list_length(list);
                free(head->value);
                free(head);
        }
}

void
linked_list_remove_last(linked_list *list, void *buffer)
{
        if (!linked_list_is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                node *tail = NULL;

                if (linked_list_length(list) == 1) {
                        tail = list->head;

                        list->head = NULL;
                        list->tail = NULL;
                } else {
                        node *previous = get_node(list, list_end - 1);

                        tail = previous->next;
                        previous->next = NULL;
                }

                if (buffer != NULL && tail != NULL)
                        memmove(buffer, tail->value, list->esize);

                decrease_list_length(list);
                free(tail->value);
                free(tail);
        }
}

void
linked_list_insert_obj_at(linked_list *list, void *object, int index)
{
        if (list != NULL) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_length || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        linked_list_free(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        linked_list_insert_first(list, object);
                } else if (index == list_end) {
                        linked_list_insert_last(list, object);
                } else {
                        node *previous = get_node(list, index - 1);
                        node *current = previous->next;

                        node *new_node = malloc(sizeof(node));

                        if (new_node != NULL) {
                                *new_node = (node) {
                                        .next = current,
                                        .value = copy_object(object, list->esize),
                                };

                                if (new_node->value == NULL) {
                                        fprintf(stderr, "***error creating object***\n");
                                        free(new_node);
                                        linked_list_free(list);
                                        exit(EXIT_FAILURE);
                                }

                                previous->next = new_node;

                                if (list->tail == NULL)
                                        list->tail = new_node;

                                increase_list_length(list);
                        }
                }
        }
}

void *
linked_list_get_obj_at(linked_list *list, int index)
{
        if (!linked_list_is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        linked_list_free(list);
                        exit(EXIT_FAILURE);
                }

                node *node = get_node(list, index);

                return node->value;
        }

        return NULL;
}

void
linked_list_remove_obj_at(linked_list *list, int index, void *buffer)
{
        if (!linked_list_is_empty(list)) {
                const size_t list_length = list->length;
                const size_t list_end = list_length - 1;

                if (index > list_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        linked_list_free(list);
                        exit(EXIT_FAILURE);
                }

                if (index == 0) {
                        linked_list_remove_first(list, buffer);
                } else if (index == list_end) {
                        linked_list_remove_last(list, buffer);
                } else {
                        node *previous = get_node(list, index - 1);
                        node *current = previous->next;

                        previous->next = current->next;

                        if (buffer != NULL && current != NULL)
                                memmove(buffer, current->value, list->esize);

                        free(current->value);
                        free(current);
                        decrease_list_length(list);
                }
        }
}

void
linked_list_show(linked_list *list, to_string_fn to_string, bool reverse)
{
        if (!linked_list_is_empty(list)) {
                const size_t list_length = list->length;

                int start = reverse ? list_length : 0;
                int end = reverse ? 0 : list_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(get_node(list, i)->value);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(get_node(list, i)->value);
                }
        }
}

void
linked_list_free(linked_list *list)
{
        if (list != NULL) {
                while (!linked_list_is_empty(list))
                        linked_list_remove_first(list, NULL);

                list->esize = 0;
                list->length = 0;

                free(list);
                list = NULL;
        }
}
