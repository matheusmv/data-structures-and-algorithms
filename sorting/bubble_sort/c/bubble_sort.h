#ifndef _BUBBLE_SORT
#define _BUBBLE_SORT

#include <stdlib.h>
#include <stdbool.h>

typedef int (*__compare_obj_fn)(void *a, void *b);
typedef __compare_obj_fn compare_obj_fn;

/*
    - Best Case: O(n)
    - Worst Case: O(n^2)
    - Not recommended for large data sets
*/
void b_sort(void *array, size_t size, int arr_length, compare_obj_fn comparator);

#endif
