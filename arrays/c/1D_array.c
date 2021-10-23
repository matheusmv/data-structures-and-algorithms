#include <stdio.h>
#include <stdlib.h>

void static_1D_array()
{
        int sarr[5] = { 1, 2, 3, 4 ,5 };

        size_t arr_size = sizeof(sarr) / sizeof(sarr[0]);

        for (int index = 0; index < arr_size; index++)
                printf("%d\t", sarr[index]);

        printf("\n");
}

void dynamic_1D_array()
{
        size_t arr_size = 5;

        int *darr = malloc(arr_size * sizeof(int));

        for (int index = 0; index < arr_size; index++)
                darr[index] = index;

        for (int index = 0; index < arr_size; index++)
                printf("%d\t", darr[index]);

        printf("\n");

        if (darr != NULL) {
                free(darr);
                darr = NULL;
        }
}

int main(int argc, char *argv[])
{
        static_1D_array();
        dynamic_1D_array();

        return EXIT_SUCCESS;
}
