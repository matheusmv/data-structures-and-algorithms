#ifndef _INSERTION_SORT
#define _INSERTION_SORT

#include "data_types.h"

#include <stdbool.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(n)
    - Worst Case: O(n^2)
    - Efficient for small data sets
    - Stable: does not change the order of equal data
    - Able to sort the data as it receives it
*/
void i_sort(object *array, size_t arr_length, compare_obj_fn comparator);

#endif
