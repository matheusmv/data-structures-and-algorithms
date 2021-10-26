#include "data_types.h"

struct map {
        int key;
        size_t value;
};

static struct map lookup_table[] = {
    {CHAR_TYPE, sizeof(char *)},
    {INT_TYPE, sizeof(int *)},
    {LONG_TYPE, sizeof(long *)},
    {FLOAT_TYPE, sizeof(float *)},
    {DOUBLE_TYPE, sizeof(double *)},
    {STATE_TYPE, sizeof(struct state *)},
    {USER_TYPE, sizeof(struct user *)},
};

int get_object_type(int key)
{
        const size_t NKEYS = (sizeof(lookup_table) / sizeof(struct map)) - 1;

        if (key < 0 || key > NKEYS) {
                fprintf(stderr, "get_type_type() failed. Invalid key\n");
                exit(EXIT_FAILURE);
        }

        return lookup_table[key].key;
}

size_t get_object_size(int key)
{
        const size_t NKEYS = (sizeof(lookup_table) / sizeof(struct map)) - 1;

        if (key < 0 || key > NKEYS) {
                fprintf(stderr, "get_type_size() failed. Invalid key\n");
                exit(EXIT_FAILURE);
        }

        return lookup_table[key].value;
}

void *get_object(struct object *obj)
{
        switch (obj->type) {
        case CHAR_TYPE:
                return &obj->_char;
        case INT_TYPE:
                return &obj->_int;
        case LONG_TYPE:
                return &obj->_long;
        case FLOAT_TYPE:
                return &obj->_float;
        case DOUBLE_TYPE:
                return &obj->_double;
        case STATE_TYPE:
                return &obj->_state;
        case USER_TYPE:
                return &obj->_user;
        default:
                return NULL;
        }
}
