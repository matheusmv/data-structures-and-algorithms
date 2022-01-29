#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum traversal_mode {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
} traversal_mode;

typedef struct binary_tree binary_tree;

typedef int (*comparator_fn)(void *a, void *b);
typedef void (*to_string_fn)(void *object);

binary_tree *binary_tree_create(size_t element_size);
size_t binary_tree_nnodes(binary_tree *tree);
bool binary_tree_is_empty(binary_tree *tree);
void binary_tree_insert(binary_tree *tree, void *object, comparator_fn comparator);
int binary_tree_remove(binary_tree *tree, void *buffer);
int binary_tree_remove_obj(binary_tree *tree, void *object, comparator_fn comparator, void *buffer);
void *binary_tree_search_obj(binary_tree *tree, void *object, comparator_fn comparator);
void binary_tree_show(binary_tree *tree, traversal_mode mode, to_string_fn to_string);
void binary_tree_free(binary_tree **tree);

#endif
