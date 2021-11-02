#ifndef _SELECTION_SORT
#define _SELECTION_SORT

#include "data_types.h"

#include <stdbool.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(n^2)
    - Worst Case: O(n^2)
    - Not recommended for large data sets
    - Stable: does not change the order of equal data
*/
void s_sort(object *array, size_t arr_length, compare_obj_fn comparator);

#endif
