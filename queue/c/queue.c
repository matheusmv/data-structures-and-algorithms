#include "queue.h"

#include <stdio.h>
#include <string.h>

typedef struct node node;
struct node {
        void *value;
        node *next;
};

typedef struct queue queue;
struct queue {
        size_t element_size;
        size_t length;
        node   *start;
        node   *end;
};

static void
increase_queue_length(queue *queue)
{
        queue->length += 1;
}

static void
decrease_queue_length(queue *queue)
{
        const size_t queue_length = queue->length;

        if (queue_length > 0) {
                queue->length -= 1;
        }
}

static void *
copy_object(const void *obj, size_t obj_size)
{
        void *copy;

        copy = malloc(obj_size);

        memcpy(copy, obj, obj_size);

        return copy;
}

queue *
queue_new(size_t element_size)
{
        queue *new_queue = malloc(sizeof(queue));
        if (new_queue == NULL) {
                return NULL;
        }

        *new_queue = (queue) {
                .element_size = element_size,
                .length = 0,
                .start = NULL,
                .end = NULL,
        };

        return new_queue;
}

size_t
queue_length(queue *queue)
{
        return queue->length;
}

bool
queue_is_empty(queue *queue)
{
        return queue->end == NULL;
}

void
queue_enqueue(queue *queue, void *object)
{
        if (queue != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *end = queue->end;

                        if (!queue_is_empty(queue))
                                end->next = new_node;

                        *new_node = (node) {
                                .next = NULL,
                                .value = copy_object(object, queue->element_size),
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                free(new_node);
                                queue_free(&queue);
                                exit(EXIT_FAILURE);
                        }

                        if (queue->start == NULL) {
                                queue->start = new_node;
                        }

                        queue->end = new_node;

                        increase_queue_length(queue);
                }
        }
}

void
queue_dequeue(queue *queue, void *buffer)
{
        if (!queue_is_empty(queue)) {
                node *start = queue->start;

                if (queue_length(queue) == 1) {
                        queue->start = NULL;
                        queue->end = NULL;
                } else {
                        queue->start = start->next;
                }

                if (buffer != NULL && start != NULL) {
                        memmove(buffer, start, queue->element_size);
                }

                decrease_queue_length(queue);
                free(start->value);
                free(start);
        }
}

void *
queue_peek(queue *queue)
{
        if (!queue_is_empty(queue)) {
                return queue->start->value;
        }

        return NULL;
}

static node *
get_node(queue *queue, size_t index)
{
        if (!queue_is_empty(queue)) {
                const size_t queue_length = queue->length;
                const size_t queue_end = queue_length - 1;

                if (index > queue_end) {
                        fprintf(stderr, "***index [%ld] out of bounds***\n", index);
                        queue_free(&queue);
                        exit(EXIT_FAILURE);
                }

                node *node = queue->start;

                if (index == queue_end) {
                        node = queue->end;
                } else {
                        for (size_t i = 0; i < index; i++) {
                                node = node->next;
                        }
                }

                return node;
        }

        return NULL;
}

void
queue_show(queue *queue, to_string_fn to_string, bool reverse)
{
        if (!queue_is_empty(queue)) {
                const size_t queue_length = queue->length;

                size_t start = reverse ? queue_length : 0;
                size_t end = reverse ? 0 : queue_length;

                if (reverse) {
                        for (size_t i = start - 1; i > end; --i) {
                                to_string(get_node(queue, i)->value);
                        }
                } else {
                        for (size_t i = start; i < end; ++i) {
                                to_string(get_node(queue, i)->value);
                        }
                }
        }
}

void
queue_free(queue **queue)
{
        if (queue != NULL && *queue != NULL) {
                while (!queue_is_empty(*queue)) {
                        queue_dequeue(*queue, NULL);
                }

                (*queue)->length = 0;
                (*queue)->start = NULL;
                (*queue)->end = NULL;

                free(*queue);
                *queue = NULL;
        }
}
