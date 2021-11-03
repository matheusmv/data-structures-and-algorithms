#ifndef _MERGE_SORT
#define _MERGE_SORT

#include "data_types.h"

#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef int (*__compare_obj_fn)(object a, object b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(nlogn)
    - Worst Case: O(nlogn)
    - Stable: does not change the order of equal data
    - Downside: recursive and uses a helper array during sorting
*/
void m_sort(object *array, size_t arr_length, compare_obj_fn comparator);

#endif
