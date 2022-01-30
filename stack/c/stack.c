#include "stack.h"

#include <stdio.h>
#include <string.h>

typedef struct node node;
struct node {
        void *value;
        node *next;
};

typedef struct stack stack;
struct stack {
        size_t element_size;
        size_t length;
        node   *top;
        node   *base;
};

static void
increase_stack_length(stack *stack)
{
        stack->length += 1;
}

static void
decrease_stack_length(stack *stack)
{
        const size_t stack_length = stack->length;

        if (stack_length > 0) {
                stack->length -= 1;
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

stack *
stack_new(size_t element_size)
{
        stack *new_stack = malloc(sizeof(stack));
        if (new_stack == NULL) {
                return NULL;
        }

        *new_stack = (stack) {
                .element_size = element_size,
                .length = 0,
                .top = NULL,
                .base = NULL,
        };

        return new_stack;
}

size_t
stack_length(stack *stack)
{
        return stack->length;
}

bool
stack_is_empty(stack *stack)
{
        return stack->base == NULL;
}

void
stack_push(stack *stack, void *object)
{
        if (stack != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        node *top = stack->top;

                        *new_node = (node) {
                                .next = top,
                                .value = copy_object(object, stack->element_size)
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object***\n");
                                free(new_node);
                                stack_free(&stack);
                                exit(EXIT_FAILURE);
                        }

                        if (stack->base == NULL) {
                                stack->base = new_node;
                        }

                        stack->top = new_node;

                        increase_stack_length(stack);
                }
        }
}

void
stack_pop(stack *stack)
{
        if (!stack_is_empty(stack)) {
                node *top = stack->top;

                if (stack_length(stack) == 1) {
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

void *
stack_peek(stack *stack)
{
        if (!stack_is_empty(stack)) {
                return stack->top->value;
        }

        return NULL;
}

static node *
get_node(stack *stack, size_t index)
{
        if (!stack_is_empty(stack)) {
                const size_t stack_length = stack->length;
                const size_t stack_end = stack_length - 1;

                if (index > stack_end) {
                        fprintf(stderr, "***index [%ld] out of bounds***\n", index);
                        stack_free(&stack);
                        exit(EXIT_FAILURE);
                }

                node *node = stack->top;

                if (index == stack_end) {
                        node = stack->base;
                } else {
                        for (size_t i = 0; i < index; ++i) {
                                node = node->next;
                        }
                }

                return node;
        }

        return NULL;
}

void
stack_show(stack *stack, to_string_fn to_string, bool reverse)
{
        if (!stack_is_empty(stack)) {
                const size_t stack_length = stack->length;

                size_t start = reverse ? stack_length : 0;
                size_t end = reverse ? 0 : stack_length;

                if (reverse) {
                        for (size_t i = start - 1; i > end; --i) {
                                to_string(get_node(stack, i)->value);
                        }
                } else {
                        for (size_t i = start; i < end; ++i) {
                                to_string(get_node(stack, i)->value);
                        }
                }
        }
}

void
stack_free(stack **stack)
{
        if (stack != NULL && *stack != NULL) {
                while (!stack_is_empty(*stack)) {
                        stack_pop(*stack);
                }

                (*stack)->length = 0;
                (*stack)->top = NULL;
                (*stack)->base = NULL;

                free(*stack);
                *stack = NULL;
        }
}
