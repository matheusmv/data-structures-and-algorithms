#include "deque.h"

typedef struct __node {
        struct object value;
        struct __node *prev;
        struct __node *next;
} node;

typedef struct __deque {
        int type;
        size_t length;
        struct __node *head;
        struct __node *tail;
} deque;

static void increase_deque_length(deque *deque)
{
        deque->length += 1;
}

static void decrease_deque_length(deque *deque)
{
        const size_t deque_length = deque->length;

        if (deque_length > 0)
                deque->length -= 1;
}

deque *new_deque(int type)
{
        deque *new_deque = malloc(sizeof(deque));

        if (new_deque == NULL)
                return NULL;

        const int deque_type = get_object_type(type);

        *new_deque = (deque) {
                .type = deque_type,
                .length = 0,
                .head = NULL,
                .tail = NULL,
        };

        return new_deque;
}

size_t get_length(deque *deque)
{
        return deque->length;
}

bool is_empty(deque *deque)
{
        return deque->head == NULL;
}

void insert_first(deque *deque, struct object object)
{
        if (deque != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *head = deque->head;

                        if (!is_empty(deque))
                                head->prev = new_node;

                        *new_node = (node) {
                                .prev = NULL,
                                .next = head,
                                .value = object,
                        };

                        if (deque->tail == NULL)
                                deque->tail = new_node;

                        deque->head = new_node;

                        increase_deque_length(deque);
                }
        }
}

void insert_last(deque *deque, struct object object)
{
        if (deque != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *tail = deque->tail;

                        if (!is_empty(deque))
                                tail->next = new_node;

                        *new_node = (node) {
                                .prev = tail,
                                .next = NULL,
                                .value = object,
                        };

                        if (deque->head == NULL)
                                deque->head = new_node;

                        deque->tail = new_node;

                        increase_deque_length(deque);
                }
        }
}

struct result remove_first(deque *deque)
{
        if (!is_empty(deque)) {
                node *head = deque->head;

                if (get_length(deque) == 1) {
                        deque->head = NULL;
                        deque->tail = NULL;
                } else {
                        deque->head = head->next;
                        deque->head->prev = NULL;
                }

                struct result obj = get_object(&head->value, deque->type);

                decrease_deque_length(deque);
                free(head);

                return obj;
        }

        return (struct result) { .is_present = false };
}

struct result remove_last(deque *deque)
{
        if (!is_empty(deque)) {
                node *tail = deque->tail;

                if (get_length(deque) == 1) {
                        deque->head = NULL;
                        deque->tail = NULL;
                } else {
                        deque->tail = tail->prev;
                        deque->tail->next = NULL;
                }

                struct result obj = get_object(&tail->value, deque->type);

                decrease_deque_length(deque);
                free(tail);

                return obj;
        }

        return (struct result) { .is_present = false };
}

struct result peek_first(deque *deque)
{
        if (!is_empty(deque)) {
                node *head = deque->head;

                return get_object(&head->value, deque->type);
        }

        return (struct result) { .is_present = false };
}

struct result peek_last(deque *deque)
{
        if (!is_empty(deque)) {
                node *tail = deque->tail;

                return get_object(&tail->value, deque->type);
        }

        return (struct result) { .is_present = false };
}

void show_deque(deque *deque, void (*to_string)(struct object object), bool reverse)
{
        if (!is_empty(deque)) {
                node *node = reverse ? deque->tail : deque->head;

                if (reverse) {
                        while (node != NULL) {
                                to_string(node->value);
                                node = node->prev;
                        }
                }

                while (node != NULL) {
                        to_string(node->value);
                        node = node->next;
                }
        }
}

void destroy_deque(deque *deque)
{
        if (deque != NULL) {
                while (!is_empty(deque))
                        remove_first(deque);

                deque->type = -1;
                deque->length = -1;
                deque->head = NULL;
                deque->tail = NULL;

                free(deque);
                deque = NULL;
        }
}
