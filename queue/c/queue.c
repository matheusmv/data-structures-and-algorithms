#include "queue.h"

typedef struct __node {
        struct object value;
        struct __node *next;
} node;

typedef struct __queue {
        int type;
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

queue *new_queue(int type)
{
        queue *new_queue = malloc(sizeof(queue));

        if (new_queue == NULL)
                return NULL;

        const int queue_type = get_object_type(type);

        *new_queue = (queue) {
                .type = queue_type,
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

void enqueue(queue *queue, struct object object)
{
        if (queue != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *end = queue->end;

                        if (!is_empty(queue))
                                end->next = new_node;

                        *new_node = (node) {
                                .next = NULL,
                                .value = object,
                        };

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
                free(start);
        }
}

void *peek(queue *queue)
{
        if (!is_empty(queue)) {
                node *start = queue->start;
                const int queue_type = queue->type;

                return get_object(&start->value, queue_type);
        }

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

void show_queue(queue *queue, void (*to_string)(struct object object), bool reverse)
{
        if (!is_empty(queue)) {
                const size_t queue_length = queue->length;

                int start = reverse ? queue_length : 0;
                int end = reverse ? 0 : queue_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(*(struct object *) get_node(queue, i));
                } else {
                        for (int i = start; i < end; i++)
                                to_string(*(struct object *) get_node(queue, i));
                }
        }
}

void destroy_queue(queue *queue)
{
        if (queue != NULL) {
                while (!is_empty(queue))
                        dequeue(queue);

                queue->type = -1;
                queue->length = -1;
                queue->start = NULL;
                queue->end = NULL;

                free(queue);
                queue = NULL;
        }
}
