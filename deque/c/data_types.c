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
    {STUDENT_TYPE, sizeof(struct student *)},
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

struct result get_object(struct object *obj, int type)
{
        struct result result;

        switch (type) {
        case CHAR_TYPE:
        case INT_TYPE:
        case LONG_TYPE:
        case FLOAT_TYPE:
        case DOUBLE_TYPE:
        case STUDENT_TYPE:
                result = (struct result) {
                        .is_present = true,
                        .object = *obj
                };

                return result;
        default:
                result = (struct result) {
                        .is_present = false,
                };

                return result;
        }
}
