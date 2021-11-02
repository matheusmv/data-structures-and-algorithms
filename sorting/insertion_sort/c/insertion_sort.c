#include "insertion_sort.h"

static bool is_empty(object *array)
{
        return array == NULL;
}

void i_sort(object *array, size_t arr_length, compare_obj_fn comparator)
{
        if (is_empty(array))
                return;

        int i, j;
        object aux;
        size_t end = arr_length;

        for (i = 1; i < end; i++) {
                aux = array[i];

                for (j = i; (j > 0) && (comparator(aux, array[j - 1]) < 0); j--) {
                        array[j] = array[j - 1];
                }

                array[j] = aux;
        }
}
