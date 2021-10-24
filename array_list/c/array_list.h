#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTDERROR() (strerror(errno))

struct object {
    int number;
    char state[50];
    char abbreviation[50];
};

struct array_list {
    struct object *array;
    size_t size;
    size_t length;
};

struct array_list new_array_list(size_t);
size_t get_size(struct array_list *);
size_t get_length(struct array_list *);
void append_obj(struct array_list *, struct object);
void remove_obj(struct array_list *);
void add_obj_at(struct array_list *, struct object, int);
struct object get_obj_at(struct array_list *, int);
void remove_obj_at(struct array_list *, int);
void destroy_array_list(struct array_list *);

#endif
