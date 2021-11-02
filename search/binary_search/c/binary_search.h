#ifndef _BINARY_SEARCH
#define _BINARY_SEARCH

#include "data_types.h"

#include <stdbool.h>
#include <string.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

result binary_search(object *array, size_t arr_length, object key, compare_obj_fn comparator);

#endif
