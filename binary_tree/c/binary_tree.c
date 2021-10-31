#include "binary_tree.h"

typedef struct __node {
        struct object value;
        struct __node *left_node;
        struct __node *right_node;
} node;

typedef struct __binary_tree {
        int type;
        size_t number_of_nodes;
        struct __node *root_node;
} binary_tree;

static void increase_number_of_nodes(binary_tree *tree)
{
        tree->number_of_nodes += 1;
}

static void decrease_number_of_nodes(binary_tree *tree)
{
        const size_t number_of_nodes = tree->number_of_nodes;

        if (number_of_nodes > 0)
                tree->number_of_nodes -= 1;
}

binary_tree *new_binary_tree(int type)
{
        binary_tree *tree = malloc(sizeof(binary_tree));

        if (tree == NULL)
                return NULL;

        const int tree_type = get_object_type(type);

        *tree = (binary_tree) {
                .type = tree_type,
                .number_of_nodes = 0,
                .root_node = NULL,
        };

        return tree;
}

size_t get_number_of_nodes(binary_tree *tree)
{
        return tree->number_of_nodes;
}

bool is_empty(binary_tree *tree)
{
        return tree->root_node == NULL;
}

void insert_obj(binary_tree *tree, struct object object,
                bool (*is_bigger_than)(struct object a, struct object b))
{
        if (tree != NULL) {
                node *new_node = malloc(sizeof(node));

                if (new_node != NULL) {
                        *new_node = (node) {
                                .value = object,
                                .left_node = NULL,
                                .right_node = NULL,
                        };

                        if (is_empty(tree)) {
                                tree->root_node = new_node;
                        } else {
                                node *current = tree->root_node;
                                node *parent = NULL;

                                while (1) {
                                        parent = current;

                                        if (is_bigger_than(object, parent->value)) {
                                                current = current->left_node;

                                                if (current == NULL) {
                                                        parent->left_node = new_node;
                                                        increase_number_of_nodes(tree);
                                                        return;
                                                }
                                        } else {
                                                current = current->right_node;

                                                if (current == NULL) {
                                                        parent->right_node = new_node;
                                                        increase_number_of_nodes(tree);
                                                        return;
                                                }
                                        }
                                }
                        }
                }
        }
}

static node *remove_node(node *current)
{
        node *aux_1 = NULL;
        node *aux_2 = NULL;

        if (current->left_node == NULL) {
                aux_2 = current->right_node;
                free(current);
                return aux_2;
        }

        aux_1 = current;
        aux_2 = current->left_node;

        while (aux_2->right_node != NULL) {
                aux_1 = aux_2;
                aux_2 = aux_2->right_node;
        }

        if (aux_1 != current) {
                aux_1->right_node = aux_2->left_node;
                aux_2->left_node = current->left_node;
        }

        aux_2->right_node = current->right_node;

        free(current);

        return aux_2;
}

struct result remove_obj(binary_tree *tree)
{
        if (!is_empty(tree)) {
                node *current = tree->root_node;

                struct object obj_removed = current->value;

                tree->root_node = remove_node(current);

                decrease_number_of_nodes(tree);

                return get_object(&obj_removed, tree->type);
        }

        return (struct result) { .is_present = false };
}

struct result find_and_remove_obj(
        binary_tree *tree,
        struct object object,
        bool (*equals)(struct object a, struct object b),
        bool (*is_bigger_than)(struct object a, struct object b))
{
        if (!is_empty(tree)) {
                struct object value;
                node *current = tree->root_node;
                node *parent = NULL;

                while (current != NULL) {
                        if (equals(object, current->value)) {
                                value = current->value;

                                if (current == tree->root_node) {
                                        tree->root_node = remove_node(current);
                                } else {
                                        if (current == parent->right_node)
                                                parent->right_node = remove_node(current);
                                        else
                                                parent->left_node = remove_node(current);
                                }

                                decrease_number_of_nodes(tree);
                                return get_object(&value, tree->type);;
                        }

                        parent = current;

                        if (is_bigger_than(object, parent->value)) {
                                current = current->left_node;
                        } else {
                                current = current->right_node;
                        }
                }
        }

        return (struct result) { .is_present = false };
}

struct result search_obj(
        binary_tree *tree,
        struct object object,
        bool (*equals)(struct object a, struct object b),
        bool (*is_bigger_than)(struct object a, struct object b))
{
        if (!is_empty(tree)) {
                node *current = tree->root_node;

                while (current != NULL) {
                        if (equals(current->value, object))
                                return get_object(&current->value, tree->type);

                        if (is_bigger_than(object, current->value)) {
                                current = current->left_node;
                        } else {
                                current = current->right_node;
                        }
                }
        }

        return (struct result) { .is_present = false };
}

static void pre_order_traversal(node *node, void (*to_string)(struct object object))
{
        if (node != NULL) {
                to_string(node->value);
                pre_order_traversal(node->left_node, to_string);
                pre_order_traversal(node->right_node, to_string);
        }
}

static void in_order_traversal(node *node, void (*to_string)(struct object object))
{
        if (node != NULL) {
                in_order_traversal(node->left_node, to_string);
                to_string(node->value);
                in_order_traversal(node->right_node, to_string);
        }
}

static void post_order_traversal(node *node, void (*to_string)(struct object object))
{
        if (node != NULL) {
                post_order_traversal(node->left_node, to_string);
                post_order_traversal(node->right_node, to_string);
                to_string(node->value);
        }
}

void show_binary_tree(binary_tree *tree, void (*to_string)(struct object object), int traversal_mode)
{
        if (!is_empty(tree)) {
                node *root = tree->root_node;

                switch (traversal_mode) {
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

static void destroy_node(node *node)
{
        if (node == NULL)
                return;

        destroy_node(node->left_node);
        destroy_node(node->right_node);

        free(node);
        node = NULL;
}

void destroy_binary_tree(binary_tree *tree)
{
        if (tree != NULL) {
                node *root = tree->root_node;

                destroy_node(root);

                tree->type = -1;
                tree->number_of_nodes = -1;

                free(tree);
                tree = NULL;
        }
}
