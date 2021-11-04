#include "data_types.h"

struct map {
        obj_type key;
        size_t value;
};

static struct map lookup_table[] = {
    {CHAR_TYPE, sizeof(char)},
    {INT_TYPE, sizeof(int)},
    {LONG_TYPE, sizeof(long)},
    {FLOAT_TYPE, sizeof(float)},
    {DOUBLE_TYPE, sizeof(double)},
    {STATE_TYPE, sizeof(struct state)},
    {USER_TYPE, sizeof(struct user)},
};

#define NKEYS (sizeof(lookup_table) / sizeof(struct map)) - 1

obj_type get_object_type(obj_type key)
{
        if (key < 0 || key > NKEYS) {
                fprintf(stderr, "get_type_type() failed. Invalid key\n");
                exit(EXIT_FAILURE);
        }

        return lookup_table[key].key;
}

size_t get_object_size(obj_type key)
{
        if (key < 0 || key > NKEYS) {
                fprintf(stderr, "get_type_size() failed. Invalid key\n");
                exit(EXIT_FAILURE);
        }

        return lookup_table[key].value;
}

result get_object(object *object, obj_type type)
{
        result result = (struct result) {
                .is_present = false,
        };

        switch (type) {
        case CHAR_TYPE:
        case INT_TYPE:
        case LONG_TYPE:
        case FLOAT_TYPE:
        case DOUBLE_TYPE:
        case STATE_TYPE:
        case USER_TYPE:
                result = (struct result) {
                        .is_present = true,
                        .object = *object,
                };

                return result;
        default:
                return result;
        }
}
