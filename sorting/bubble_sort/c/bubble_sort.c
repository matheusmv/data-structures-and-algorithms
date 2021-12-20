#include "bubble_sort.h"

static bool is_empty(void *array)
{
        return array == NULL;
}

static void *get_index(void *array, size_t size, int index)
{
        return (void *) (((char *) array) + index * size);
}

static void swap(void *a, void *b, size_t size)
{
        unsigned char aux, *aux_a, *aux_b;

        aux_a = a;
        aux_b = b;

        for (size_t i = 0; i != size; i++) {
                aux = aux_a[i];
                aux_a[i] = aux_b[i];
                aux_b[i] = aux;
        }
}

void b_sort(void *array, size_t size, int arr_length, compare_obj_fn comparator)
{
        if (is_empty(array) || arr_length <= 0)
                return;

        int end = arr_length - 1;
        bool swapped;

        for (int i = 0; i < end; i++) {
                swapped = false;

                for (int j = 0; j < end - i; j++) {
                        void *prev = get_index(array, size, j);
                        void *next = get_index(array, size, j + 1);

                        if (comparator(prev, next) > 0) {
                                swap(prev, next, size);
                                swapped = true;
                        }
                }

                if (!swapped)
                        break;
        }
}
