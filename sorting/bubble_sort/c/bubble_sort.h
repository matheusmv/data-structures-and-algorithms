#ifndef _BUBBLE_SORT
#define _BUBBLE_SORT

#include "data_types.h"

#include <stdbool.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(n)
    - Worst Case: O(n^2)
    - Not recommended for large data sets
*/
void b_sort(object *array, size_t arr_length, compare_obj_fn comparator);

#endif
