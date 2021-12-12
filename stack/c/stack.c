#include "stack.h"

typedef struct __node {
        void *value;
        struct __node *next;
} node;

typedef struct __stack {
        size_t esize;
        size_t length;
        struct __node *top;
        struct __node *base;
} stack;

static void increase_stack_length(stack *stack)
{
        stack->length += 1;
}

static void decrease_stack_length(stack *stack)
{
        const size_t stack_length = stack->length;

        if (stack_length > 0)
                stack->length -= 1;
}

static void *copy_object(const void *obj, size_t obj_size)
{
        void *copy;

        copy = malloc(obj_size);

        memcpy(copy, obj, obj_size);

        return copy;
}

stack *new_stack(size_t element_size)
{
        stack *new_stack = malloc(sizeof(stack));

        if (new_stack == NULL)
                return NULL;

        *new_stack = (stack) {
                .esize = element_size,
                .length = 0,
                .top = NULL,
                .base = NULL,
        };

        return new_stack;
}

size_t get_length(stack *stack)
{
        return stack->length;
}

bool is_empty(stack *stack)
{
        return stack->base == NULL;
}

void push(stack *stack, void *object)
{
        if (stack != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *top = stack->top;

                        *new_node = (node) {
                                .next = top,
                                .value = copy_object(object, stack->esize)
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                destroy_stack(stack);
                                exit(EXIT_FAILURE);
                        }

                        if (stack->base == NULL)
                                stack->base = new_node;

                        stack->top = new_node;

                        increase_stack_length(stack);
                }
        }
}

void pop(stack *stack)
{
        if (!is_empty(stack)) {
                node *top = stack->top;

                if (get_length(stack) == 1) {
                        stack->top = NULL;
                        stack->base = NULL;
                } else {
                        stack->top = top->next;
                }

                decrease_stack_length(stack);
                free(top->value);
                free(top);
        }
}

void *peek(stack *stack)
{
        if (!is_empty(stack))
                return stack->top->value;

        return NULL;
}

static node *get_node(stack *stack, int index)
{
        if (!is_empty(stack)) {
                const size_t stack_length = stack->length;
                const size_t stack_end = stack_length - 1;

                if (index > stack_end || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_stack(stack);
                        exit(EXIT_FAILURE);
                }

                node *node = stack->top;

                if (index == stack_end) {
                        node = stack->base;
                } else {
                        for (int i = 0; i < index; i++)
                                node = node->next;
                }

                return node;
        }

        return NULL;
}

void show_stack(stack *stack, void (*to_string)(void *object), bool reverse)
{
        if (!is_empty(stack)) {
                const size_t stack_length = stack->length;

                int start = reverse ? stack_length : 0;
                int end = reverse ? 0 : stack_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(get_node(stack, i)->value);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(get_node(stack, i)->value);
                }
        }
}

void destroy_stack(stack *stack)
{
        if (stack != NULL) {
                while (!is_empty(stack))
                        pop(stack);

                stack->length = -1;
                stack->top = NULL;
                stack->base = NULL;

                free(stack);
                stack = NULL;
        }
}
