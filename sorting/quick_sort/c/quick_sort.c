#include "quick_sort.h"

static bool is_empty(object *array)
{
        return array == NULL;
}

static void swap(object *a, object *b)
{
        object aux = *a;
        *a = *b;
        *b = aux;
}

static int64_t partition(object *array, int64_t start, int64_t end, compare_obj_fn comparator)
{
        object pivot = array[start];

        int64_t arr_left = start;
        int64_t arr_right = end;

        while (arr_left < arr_right) {
                while (arr_left <= end && comparator(array[arr_left], pivot) <= 0)
                        arr_left += 1;
                while (arr_right >= 0 && comparator(array[arr_right], pivot) > 0)
                        arr_right -= 1;
                if (arr_left < arr_right)
                        swap(&array[arr_left], &array[arr_right]);
        }

        array[start] = array[arr_right];
        array[arr_right] = pivot;

        return arr_right;
}

static void quick_sort(object *array, int64_t start, int64_t end, compare_obj_fn comparator)
{
        if (start >= end)
                return;

        int64_t pivot = partition(array, start, end, comparator);

        quick_sort(array, start, pivot - 1, comparator);
        quick_sort(array, pivot + 1, end, comparator);
}

void q_sort(object *array, size_t arr_length, compare_obj_fn comparator)
{
        if (is_empty(array))
                return;

        int64_t start = 0;
        int64_t end = arr_length - 1;

        quick_sort(array, start, end, comparator);
}
