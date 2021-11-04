#ifndef _QUICK_SORT
#define _QUICK_SORT

#include "data_types.h"

#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(nlogn)
    - Worst Case: O(n^2)
    - Stable: does not change the order of equal data
    - Downside: how to choose the pivot?
*/
void q_sort(object *array, size_t arr_length, compare_obj_fn comparator);

#endif
