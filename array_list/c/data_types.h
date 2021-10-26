#ifndef _ARRAY_DATA_TYPES
#define _ARRAY_DATA_TYPES

#include <stdio.h>
#include <stdlib.h>

/* custom data types */

struct state {
        int number;
        char *state;
        char *abbreviation;
};

struct user {
        char *username;
        char *password;
};

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
        int type;
        union {
                char _char;
                int _int;
                long _long;
                float _float;
                double _double;
                struct state _state;
                struct user _user;
        };
};

int get_object_type(int key);
size_t get_object_size(int key);
void *get_object(struct object *object);

#endif
