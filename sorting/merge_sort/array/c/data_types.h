#ifndef _ARRAY_DATA_TYPES
#define _ARRAY_DATA_TYPES

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* custom data types */

struct student {
        int id;
        char *name;
        float n1, n2, n3;
};

/* data type mapper */

typedef enum array_types {
        CHAR_TYPE,
        INT_TYPE,
        LONG_TYPE,
        FLOAT_TYPE,
        DOUBLE_TYPE,
        STUDENT_TYPE,
} obj_type;

typedef struct object {
        union {
                char _char;
                int _int;
                long _long;
                float _float;
                double _double;
                struct student _student;
        };
} object;

typedef struct result {
        bool is_present;
        struct object object;
} result;

obj_type get_object_type(obj_type key);
size_t get_object_size(obj_type key);
result get_object(object *object, obj_type type);

#endif
