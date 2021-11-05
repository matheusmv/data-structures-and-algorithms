#ifndef _ARRAY_DATA_TYPES
#define _ARRAY_DATA_TYPES

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* custom data types */

/* data type mapper */

enum array_types {
        CHAR_TYPE,
        INT_TYPE,
        LONG_TYPE,
        FLOAT_TYPE,
        DOUBLE_TYPE,
        STATE_TYPE,
        USER_TYPE,
};

struct object {
        union {
                char _char;
                int _int;
                long _long;
                float _float;
                double _double;
        };
};

struct result {
        bool is_present;
        struct object object;
};

typedef int64_t obj_type;
typedef struct object object;
typedef struct result result;

obj_type get_object_type(obj_type key);
size_t get_object_size(obj_type key);
result get_object(object *object, obj_type type);

#endif
