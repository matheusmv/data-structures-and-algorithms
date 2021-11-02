#include "linear_search.h"

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
int comparator(object a, object b);

int main(int argc, char *argv[])
{
        const size_t arr_len = sizeof(numbers) / sizeof(numbers[0]);

        show_array(numbers, arr_len);

        result result = linear_search(numbers, arr_len, (object) { ._int = 3 }, comparator);

        if (result.is_present)
                printf("*** \tfound\n");
        else
                printf("*** \tnot found\n");

        return EXIT_SUCCESS;
}

void show_array(object *array, size_t arr_len)
{
        for (int i = 0; i < arr_len; i++)
                printf("%d - ", array[i]._int);
        printf("\n");
}

int comparator(object a, object b)
{
        int value_a = a._int;
        int value_b = b._int;

        return value_a - value_b;
}
