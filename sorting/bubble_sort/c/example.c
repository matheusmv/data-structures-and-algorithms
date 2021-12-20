/**
 * gcc bubble_sort.c example.c -o program
 */
#include "bubble_sort.h"

#include <stdio.h>
#include <stdlib.h>

int numbers[] = { 55, 17, 2, 28, 10 ,18 ,32 ,1 ,3 ,44 };

void show_array(void *array, size_t arr_len);
int in_order(void *a, void *b);
int reverse(void *a, void *b);

int main(int argc, char *argv[])
{
        const size_t arr_len = sizeof(numbers) / sizeof(numbers[0]);

        show_array(numbers, arr_len);

        b_sort(numbers, sizeof(numbers[0]), arr_len, in_order);

        show_array(numbers, arr_len);

        b_sort(numbers, sizeof(numbers[0]), arr_len, reverse);

        show_array(numbers, arr_len);

        return EXIT_SUCCESS;
}

void show_array(void *array, size_t arr_len)
{
        int *arr = array;

        for (int i = 0; i < arr_len; i++)
                printf("%d - ", arr[i]);
        printf("\n");
}

int in_order(void *a, void *b)
{
        int *value_a = a;
        int *value_b = b;

        return *value_a - *value_b;
}

int reverse(void *a, void *b)
{
        int *value_a = a;
        int *value_b = b;

        return *value_b - *value_a;
}
