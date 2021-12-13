#include "queue.h"

typedef struct __node {
        void *value;
        struct __node *next;
} node;

typedef struct __queue {
        size_t esize;
        size_t length;
        struct __node *start;
        struct __node *end;
} queue;

static void increase_queue_length(queue *queue)
{
        queue->length += 1;
}

static void decrease_queue_length(queue *queue)
{
        const size_t queue_length = queue->length;

        if (queue_length > 0)
                queue->length -= 1;
}

static void *copy_object(const void *obj, size_t obj_size)
{
        void *copy;

        copy = malloc(obj_size);

        memcpy(copy, obj, obj_size);

        return copy;
}

queue *new_queue(size_t element_size)
{
        queue *new_queue = malloc(sizeof(queue));

        if (new_queue == NULL)
                return NULL;

        *new_queue = (queue) {
                .esize = element_size,
                .length = 0,
                .start = NULL,
                .end = NULL,
        };

        return new_queue;
}

size_t get_length(queue *queue)
{
        return queue->length;
}

bool is_empty(queue *queue)
{
        return queue->end == NULL;
}

void enqueue(queue *queue, void *object)
{
        if (queue != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *end = queue->end;

                        if (!is_empty(queue))
                                end->next = new_node;

                        *new_node = (node) {
                                .next = NULL,
                                .value = copy_object(object, queue->esize),
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                free(new_node);
                                destroy_queue(queue);
                                exit(EXIT_FAILURE);
                        }

                        if (queue->start == NULL)
                                queue->start = new_node;

                        queue->end = new_node;

                        increase_queue_length(queue);
                }
        }
}

void dequeue(queue *queue)
{
        if (!is_empty(queue)) {
                node *start = queue->start;

                if (get_length(queue) == 1) {
                        queue->start = NULL;
                        queue->end = NULL;
                } else {
                        queue->start = start->next;
                }

                decrease_queue_length(queue);
                free(start->value);
                free(start);
        }
}

void *peek(queue *queue)
{
        if (!is_empty(queue))
                return queue->start->value;

        return NULL;
}

static node *get_node(queue *queue, int index)
{
        if (!is_empty(queue)) {
                const size_t queue_length = queue->length;
                const size_t queue_end = queue_length - 1;

                if (index > queue_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_queue(queue);
                        exit(EXIT_FAILURE);
                }

                node *node = queue->start;

                if (index == queue_end) {
                        node = queue->end;
                } else {
                        for (int i = 0; i < index; i++)
                                node = node->next;
                }

                return node;
        }

        return NULL;
}

void show_queue(queue *queue, void (*to_string)(void *object), bool reverse)
{
        if (!is_empty(queue)) {
                const size_t queue_length = queue->length;

                int start = reverse ? queue_length : 0;
                int end = reverse ? 0 : queue_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(get_node(queue, i)->value);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(get_node(queue, i)->value);
                }
        }
}

void destroy_queue(queue *queue)
{
        if (queue != NULL) {
                while (!is_empty(queue))
                        dequeue(queue);

                queue->length = -1;
                queue->start = NULL;
                queue->end = NULL;

                free(queue);
                queue = NULL;
        }
}
