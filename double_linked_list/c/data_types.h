#ifndef _ARRAY_DATA_TYPES
#define _ARRAY_DATA_TYPES

#include <stdio.h>
#include <stdlib.h>

/* custom data types */

struct student {
        int id;
        char *name;
        float n1, n2, n3;
};

/* data type mapper */

enum array_types {
        CHAR_TYPE,
        INT_TYPE,
        LONG_TYPE,
        FLOAT_TYPE,
        DOUBLE_TYPE,
        STUDENT_TYPE,
};

struct object {
        union {
                char _char;
                int _int;
                long _long;
                float _float;
                double _double;
                struct student _student;
        };
};

int get_object_type(int key);
size_t get_object_size(int key);
void *get_object(struct object *object, int type);

#endif
