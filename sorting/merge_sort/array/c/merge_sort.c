#include "merge_sort.h"

static bool is_empty(object *array)
{
        return array == NULL;
}

static void merge(object *array, size_t start, size_t mid, size_t end, compare_obj_fn comparator)
{
        size_t arr_len = end - start + 1;
        object *aux_arr = malloc(arr_len * sizeof(object));

        if (aux_arr != NULL) {
                size_t first_half = start;
                size_t second_half = mid + 1;
                bool end_of_first_half = false;
                bool end_of_second_half = false;

                for (int i = 0; i < arr_len; i++) {
                        if (!end_of_first_half && !end_of_second_half) {
                                if (comparator(array[first_half], array[second_half]) <= 0) {
                                        aux_arr[i] = array[first_half];
                                        first_half += 1;
                                } else {
                                        aux_arr[i] = array[second_half];
                                        second_half += 1;
                                }

                                if (first_half > mid)
                                        end_of_first_half = true;
                                if (second_half > end)
                                        end_of_second_half = true;
                        } else {
                                if (!end_of_first_half) {
                                        aux_arr[i] = array[first_half];
                                        first_half += 1;
                                } else {
                                        aux_arr[i] = array[second_half];
                                        second_half += 1;
                                }
                        }
                }

                for (int k = start, j = 0; j < arr_len; k++, j++) {
                        array[k] = aux_arr[j];
                }

                free(aux_arr);
                aux_arr = NULL;
        }
}

static void merge_sort(object *array, size_t start, size_t end, compare_obj_fn comparator)
{
        if (start >= end)
                return;

        size_t mid = floor((start + end) / 2);

        merge_sort(array, start, mid, comparator);
        merge_sort(array, mid + 1, end, comparator);
        merge(array, start, mid, end, comparator);
}

void m_sort(object *array, size_t arr_length, compare_obj_fn comparator)
{
        if (is_empty(array))
                return;

        size_t start = 0;
        size_t end = arr_length - 1;

        merge_sort(array, start, end, comparator);
}
