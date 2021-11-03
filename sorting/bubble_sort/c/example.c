/**
 * gcc data_types.c bubble_sort.c example.c -o program
 */
#include "bubble_sort.h"

#include <stdio.h>
#include <stdlib.h>

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

void show_array(object *array, size_t arr_len);
int in_order(object a, object b);
int reverse(object a, object b);

int main(int argc, char *argv[])
{
        const size_t arr_len = sizeof(numbers) / sizeof(numbers[0]);

        show_array(numbers, arr_len);

        b_sort(numbers, arr_len, in_order);

        show_array(numbers, arr_len);

        b_sort(numbers, arr_len, reverse);

        show_array(numbers, arr_len);

        return EXIT_SUCCESS;
}

void show_array(object *array, size_t arr_len)
{
        for (int i = 0; i < arr_len; i++)
                printf("%d - ", array[i]._int);
        printf("\n");
}

int in_order(object a, object b)
{
        int value_a = a._int;
        int value_b = b._int;

        return value_a - value_b;
}

int reverse(object a, object b)
{
        int value_a = a._int;
        int value_b = b._int;

        return value_b - value_a;
}
