#ifndef _STACK
#define _STACK

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __stack stack;

stack *new_stack(size_t element_size);
size_t get_length(stack *stack);
bool is_empty(stack *stack);
void push(stack *stack, void *object);
void pop(stack *stack);
void *peek(stack *stack);
void show_stack(stack *stack, void (*to_string)(void *object), bool reverse);
void destroy_stack(stack *stack);

#endif
