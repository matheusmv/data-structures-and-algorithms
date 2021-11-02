#ifndef _LINEAR_SEARCH
#define _LINEAR_SEARCH

#include "data_types.h"

#include <stdbool.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

result linear_search(object *array, size_t arr_length, object key, compare_obj_fn comparator);

#endif
