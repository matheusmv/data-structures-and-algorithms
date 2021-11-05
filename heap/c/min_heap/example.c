/**
 * gcc data_types.c min_heap.c example.c -o program
 */
#include "min_heap.h"

object numbers[] = {
        {._int = 55},
        {._int = 17},
        {._int = 2},
        {._int = 28},
        {._int = 10},
        {._int = 18},
        {._int = 32},
        {._int = 1},
        {._int = 3},
        {._int = 44},
};

void show_numbers(object obj);
int comparator(object a, object b);

int main(int argc, char *argv[])
{
        min_heap *heap = new_min_heap(5, INT_TYPE, comparator);

        if (heap == NULL)
                return EXIT_FAILURE;

        const size_t arr_len = sizeof(numbers) / sizeof(numbers[0]);

        for (int i = 0; i < arr_len; i++)
                insert_obj(heap, numbers[i]);

        show_heap(heap, show_numbers, IN_ORDER);
        printf("\n");

        for (int i = 0; i < arr_len; i++) {
                result result = remove_obj(heap);
                if (result.is_present)
                        show_numbers(result.object);
        }
        printf("\n");

        destroy_min_heap(heap);

        return EXIT_SUCCESS;
}

void show_numbers(object obj)
{
        int number = obj._int;

        printf("%d - ", number);
}

int comparator(object a, object b)
{
        int value_a = a._int;
        int value_b = b._int;

        return value_a - value_b;
}
