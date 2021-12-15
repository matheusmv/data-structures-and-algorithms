#ifndef _BINARY_TREE
#define _BINARY_TREE

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


typedef int (*__comparator_fn)(void *a, void *b);
typedef __comparator_fn comparator_fn;

typedef void (*__to_string_fn)(void *object);
typedef __to_string_fn to_string_fn;


binary_tree *new_binary_tree(size_t element_size);
size_t get_number_of_nodes(binary_tree *tree);
bool is_empty(binary_tree *tree);
void insert_obj(binary_tree *tree, void *object, comparator_fn comparator);
int remove_obj(binary_tree *tree, void *buffer);
int find_and_remove_obj(binary_tree *tree, void *object, comparator_fn comparator, void *buffer);
void *search_obj(binary_tree *tree, void *object, comparator_fn comparator);
void show_binary_tree(binary_tree *tree, traversal_mode mode, to_string_fn to_string);
void destroy_binary_tree(binary_tree *tree);

#endif
