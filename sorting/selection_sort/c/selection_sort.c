#include "selection_sort.h"

static bool is_empty(object *array)
{
        return array == NULL;
}

static void swapp(object *a, object *b)
{
        object aux = *a;
        *a = *b;
        *b = aux;
}

void s_sort(object *array, size_t arr_length, compare_obj_fn comparator)
{
        if (is_empty(array))
                return;

        int min_value_index = 0;
        size_t end = arr_length;

        for (int i = 0; i < end - 1; i++) {
                min_value_index = i;

                for (int j = i + 1; j < end; j++) {
                        if (comparator(array[j], array[min_value_index]) < 0)
                                min_value_index = j;
                }

                if (min_value_index != i)
                        swapp(&array[i], &array[min_value_index]);
        }
}
