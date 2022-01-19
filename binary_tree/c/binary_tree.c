#include "binary_tree.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef struct node node;
struct node {
        size_t amount;
        void *value;
        node *left_node;
        node *right_node;
};

typedef struct binary_tree binary_tree;
struct binary_tree {
        size_t esize;
        size_t number_of_nodes;
        node *root_node;
};

#define GETSTDERROR() (strerror(errno))

static void
increase_number_of_nodes(binary_tree *tree)
{
        tree->number_of_nodes += 1;
}

static void
decrease_number_of_nodes(binary_tree *tree)
{
        const size_t number_of_nodes = tree->number_of_nodes;

        if (number_of_nodes > 0)
                tree->number_of_nodes -= 1;
}

static void *
copy_object(const void *obj, size_t obj_size)
{
        void *copy;

        copy = malloc(obj_size);

        memcpy(copy, obj, obj_size);

        return copy;
}

static void
free_node(node *node)
{
        if (node != NULL) {
                if (node->value != NULL)
                        free(node->value);
                free(node);
        }
}

binary_tree *
binary_tree_create(size_t element_size)
{
        binary_tree *tree = malloc(sizeof(binary_tree));

        if (tree == NULL)
                return NULL;

        *tree = (binary_tree) {
                .esize = element_size,
                .number_of_nodes = 0,
                .root_node = NULL,
        };

        return tree;
}

size_t
binary_tree_nnodes(binary_tree *tree)
{
        return tree->number_of_nodes;
}

bool
binary_tree_is_empty(binary_tree *tree)
{
        return tree->root_node == NULL;
}

static void
insert_node(binary_tree *tree, node *new_node, comparator_fn comparator)
{
        node *current = tree->root_node;
        node *parent = NULL;

        while (1) {
                parent = current;

                if (comparator(new_node->value, parent->value) == 0) {
                        parent->amount += 1;
                        free_node(new_node);
                        return;
                }

                if (comparator(new_node->value, parent->value) > 0) {
                        current = current->right_node;

                        if (current == NULL) {
                                parent->right_node = new_node;
                                return;
                        }
                } else {
                        current = current->left_node;

                        if (current == NULL) {
                                parent->left_node = new_node;
                                return;
                        }
                }
        }
}

void
binary_tree_insert(binary_tree *tree, void *object, comparator_fn comparator)
{
        if (tree != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        *new_node = (node) {
                                .amount = 1,
                                .value = copy_object(object, tree->esize),
                                .left_node = NULL,
                                .right_node = NULL,
                        };

                        if (new_node->value == NULL) {
                                fprintf(stderr, "***error creating object. (%s)***\n", GETSTDERROR());
                                free_node(new_node);
                                binary_tree_free(tree);
                                exit(EXIT_FAILURE);
                        }

                        if (binary_tree_is_empty(tree)) {
                                tree->root_node = new_node;
                        } else {
                                insert_node(tree, new_node, comparator);
                        }

                        increase_number_of_nodes(tree);
                }
        }
}

static node *
remove_node(node *rmv_node)
{
        if (rmv_node->amount > 1) {
                rmv_node->amount -= 1;
                return rmv_node;
        }

        node *aux_1 = NULL;
        node *aux_2 = NULL;

        if (rmv_node->left_node == NULL) {
                aux_2 = rmv_node->right_node;
                free_node(rmv_node);
                return aux_2;
        }

        aux_1 = rmv_node;
        aux_2 = rmv_node->left_node;

        while (aux_2->right_node != NULL) {
                aux_1 = aux_2;
                aux_2 = aux_2->right_node;
        }

        if (aux_1 != rmv_node) {
                aux_1->right_node = aux_2->left_node;
                aux_2->left_node = rmv_node->left_node;
        }

        aux_2->right_node = rmv_node->right_node;

        free_node(rmv_node);

        return aux_2;
}

int
binary_tree_remove(binary_tree *tree, void *buffer)
{
        if (!binary_tree_is_empty(tree)) {
                node *current = tree->root_node;

                if (buffer != NULL)
                        memmove(buffer, current->value, tree->esize);

                tree->root_node = remove_node(current);

                decrease_number_of_nodes(tree);

                return 0;
        }

        return -1;
}

int
binary_tree_remove_obj(binary_tree *tree, void *object, comparator_fn comparator, void *buffer)
{
        if (!binary_tree_is_empty(tree)) {
                node *current = tree->root_node;
                node *parent = NULL;

                while (current != NULL) {
                        if (comparator(object, current->value) == 0) {
                                if (buffer != NULL)
                                        memmove(buffer, current->value, tree->esize);

                                if (current == tree->root_node) {
                                        tree->root_node = remove_node(current);
                                } else if (current == parent->right_node) {
                                        parent->right_node = remove_node(current);
                                } else {
                                        parent->left_node = remove_node(current);
                                }

                                decrease_number_of_nodes(tree);

                                return 0;
                        }

                        parent = current;

                        if (comparator(object, parent->value) > 0) {
                                current = current->right_node;
                        } else {
                                current = current->left_node;
                        }
                }
        }

        return -1;
}

void *
binary_tree_search_obj(binary_tree *tree, void *object, comparator_fn comparator)
{
        if (!binary_tree_is_empty(tree)) {
                node *current = tree->root_node;

                while (current != NULL) {
                        if (comparator(current->value, object) == 0)
                                return current->value;

                        if (comparator(object, current->value) > 0) {
                                current = current->right_node;
                        } else {
                                current = current->left_node;
                        }
                }
        }

        return NULL;
}

static void
pre_order_traversal(node *node, to_string_fn to_string)
{
        if (node != NULL) {
                to_string(node->value);
                pre_order_traversal(node->left_node, to_string);
                pre_order_traversal(node->right_node, to_string);
        }
}

static void
in_order_traversal(node *node, to_string_fn to_string)
{
        if (node != NULL) {
                in_order_traversal(node->left_node, to_string);
                to_string(node->value);
                in_order_traversal(node->right_node, to_string);
        }
}

static void
post_order_traversal(node *node, to_string_fn to_string)
{
        if (node != NULL) {
                post_order_traversal(node->left_node, to_string);
                post_order_traversal(node->right_node, to_string);
                to_string(node->value);
        }
}

void
binary_tree_show(binary_tree *tree, traversal_mode mode, to_string_fn to_string)
{
        if (!binary_tree_is_empty(tree)) {
                node *root = tree->root_node;

                switch (mode) {
                case PRE_ORDER:
                        pre_order_traversal(root, to_string);
                        break;
                case IN_ORDER:
                        in_order_traversal(root, to_string);
                        break;
                case POST_ORDER:
                        post_order_traversal(root, to_string);
                        break;
                }
        }
}

static void
destroy_node(node *node)
{
        if (node == NULL)
                return;

        destroy_node(node->left_node);
        destroy_node(node->right_node);

        free_node(node);
        node = NULL;
}

void
binary_tree_free(binary_tree *tree)
{
        if (tree != NULL) {
                node *root = tree->root_node;

                destroy_node(root);

                tree->esize = 0;
                tree->number_of_nodes = 0;

                free(tree);
                tree = NULL;
        }
}
