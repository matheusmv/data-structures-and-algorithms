#include "linked_list.h"

typedef struct __node {
        struct object value;
        struct __node *next;
} node;

typedef struct __linked_list {
        obj_type type;
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

        obj_type list_type = get_object_type(type);

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

void insert_first(linked_list *list, object object)
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

void insert_last(linked_list *list, object object)
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

result remove_first(linked_list *list)
{
        if (!is_empty(list)) {
                node *head = list->head;

                if (get_length(list) == 1) {
                        list->head = NULL;
                        list->tail = NULL;
                } else {
                        list->head = head->next;
                }

                result obj = get_object(&head->value, list->type);

                decrease_list_length(list);
                free(head);

                return obj;
        }

        return (struct result) { .is_present = false };
}

result remove_last(linked_list *list)
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

                result obj = get_object(&tail->value, list->type);

                decrease_list_length(list);
                free(tail);

                return obj;
        }

        return (struct result) { .is_present = false };
}

void insert_obj_at(linked_list *list, object object, int index)
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

result get_obj_at(linked_list *list, int index)
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

        return (struct result) { .is_present = false };
}

result remove_obj_at(linked_list *list, int index)
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

                        result obj = get_object(&current->value, list->type);

                        free(current);
                        decrease_list_length(list);

                        return obj;
                }
        }

        return (struct result) { .is_present = false };
}

void show_list(linked_list *list, to_string_fn to_string, bool reverse)
{
        if (!is_empty(list)) {
                const size_t list_length = list->length;

                int start = reverse ? list_length : 0;
                int end = reverse ? 0 : list_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(get_obj_at(list, i).object);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(get_obj_at(list, i).object);
                }
        }
}

static node *merge(node *first_half, node *second_half, compare_obj_fn comparator)
{
        node *result = NULL;

        if (first_half == NULL)
                return second_half;
        else if (second_half == NULL)
                return first_half;

        if (comparator(first_half->value, second_half->value) <= 0) {
                result = first_half;
                result->next = merge(first_half->next, second_half, comparator);
        } else {
                result = second_half;
                result->next = merge(first_half, second_half->next, comparator);
        }

        return result;
}

static void split_list(node *src, node **first_half, node **second_half)
{
        node *aux_1;
        node *aux_2;

        aux_2 = src;
        aux_1 = src->next;

        while (aux_1 != NULL) {
                aux_1 = aux_1->next;
                if (aux_1 != NULL) {
                        aux_2 = aux_2->next;
                        aux_1 = aux_1->next;
                }
        }

        *first_half = src;
        *second_half = aux_2->next;
        aux_2->next = NULL;
}

static void merge_sort(node **start, compare_obj_fn comparator)
{
        node *head = *start;

        if (head == NULL || head->next == NULL)
                return;

        node *first_half = NULL;
        node *second_half = NULL;

        split_list(head, &first_half, &second_half);

        merge_sort(&first_half, comparator);
        merge_sort(&second_half, comparator);

        *start = merge(first_half, second_half, comparator);
}

void m_sort_list(linked_list *list, compare_obj_fn comparator)
{
        if (is_empty(list))
                return;

        merge_sort(&list->head, comparator);
}

void destroy_linked_list(linked_list *list)
{
        if (list != NULL) {
                while (!is_empty(list))
                        remove_first(list);

                list->type = -1;
                list->length = -1;
                list->head = NULL;
                list->tail = NULL;

                free(list);
                list = NULL;
        }
}
