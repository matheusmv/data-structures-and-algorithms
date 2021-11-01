#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

typedef struct __binary_tree binary_tree;

typedef enum __tree_traversal_mode {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
} traversal_mode;


typedef bool (*__equals_fn)(object a, object b);
typedef __equals_fn equals_fn;

typedef bool (*__greater_than_fn)(object a, object b);
typedef __greater_than_fn greater_than_fn;

typedef void (*__to_string_fn)(object object);
typedef __to_string_fn to_string_fn;


binary_tree *new_binary_tree(obj_type type);
size_t get_number_of_nodes(binary_tree *tree);
bool is_empty(binary_tree *tree);
void insert_obj(binary_tree *tree, object object,
                equals_fn equals, greater_than_fn greater_than);
result remove_obj(binary_tree *tree);
result find_and_remove_obj(binary_tree *tree, object object,
                           equals_fn equals, greater_than_fn greater_than);
result search_obj(binary_tree *tree, object object,
                  equals_fn equals, greater_than_fn greater_than);
void show_binary_tree(binary_tree *tree, traversal_mode mode, to_string_fn to_string);
void destroy_binary_tree(binary_tree *tree);

#endif
