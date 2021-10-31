#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "data_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

enum tree_traversal_mode {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
};

typedef struct __binary_tree binary_tree;

binary_tree *new_binary_tree(int type);
size_t get_number_of_nodes(binary_tree *tree);
bool is_empty(binary_tree *tree);
void insert_obj(binary_tree *tree, struct object object,
                 bool (*is_bigger_than)(struct object a, struct object b));
struct result remove_obj(binary_tree *tree);
struct result find_and_remove_obj( binary_tree *tree, struct object object,
                 bool (*equals)(struct object a, struct object b),
                 bool (*is_bigger_than)(struct object a, struct object b));
struct result search_obj( binary_tree *tree, struct object object,
                 bool (*equals)(struct object a, struct object b),
                 bool (*is_bigger_than)(struct object a, struct object b));
void show_binary_tree(binary_tree *tree, void (*to_string)(struct object object), int traversal_mode);
void destroy_binary_tree(binary_tree *tree);

#endif
