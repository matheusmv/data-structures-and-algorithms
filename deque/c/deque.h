#ifndef _DEQUE
#define _DEQUE

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

#define IN_ORDER false
#define REVERSE true

typedef struct __deque deque;

deque *new_deque(int type);
size_t get_length(deque *deque);
bool is_empty(deque *deque);
void insert_first(deque *deque, struct object object);
void insert_last(deque *deque, struct object object);
struct result remove_first(deque *deque);
struct result remove_last(deque *deque);
struct result peek_first(deque *deque);
struct result peek_last(deque *deque);
void show_deque(deque *deque, void (*to_string)(struct object object), bool reverse);
void destroy_deque(deque *deque);

#endif
