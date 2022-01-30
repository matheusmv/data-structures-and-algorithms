#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

#define IN_ORDER false
#define REVERSE  true

typedef struct stack stack;

typedef void (*to_string_fn)(void *object);

stack *stack_new(size_t element_size);
size_t stack_length(stack *stack);
bool stack_is_empty(stack *stack);
void stack_push(stack *stack, void *object);
void stack_pop(stack *stack, void *buffer);
void *stack_peek(stack *stack);
void stack_show(stack *stack, to_string_fn to_string, bool reverse);
void stack_free(stack **stack);

#endif
