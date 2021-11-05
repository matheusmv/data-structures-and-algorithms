#include "bubble_sort.h"

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

void b_sort(object *array, size_t arr_length, compare_obj_fn comparator)
{
        if (is_empty(array))
                return;

        size_t end = arr_length - 1;
        bool swapped;

        for (int i = 0; i < end; i++) {
                swapped = false;

                for (int j = 0; j < end - i; j++) {
                        if (comparator(array[j], array[j + 1]) > 0) {
                                swap(&array[j], &array[j + 1]);
                                swapped = true;
                        }
                }

                if (!swapped)
                        break;
        }
}
