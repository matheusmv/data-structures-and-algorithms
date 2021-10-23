#include <stdio.h>
#include <stdlib.h>

void static_2D_array()
{
        int sarr[3][3] = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
        };

        size_t line_size = sizeof(sarr) / sizeof(sarr[0]);
        size_t colm_size = sizeof(sarr[0]) / sizeof(int);

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        printf("%d\t", sarr[line][colm]);
                }
                printf("\n");
        }
}

void dynamic_2D_array()
{
        size_t line_size = 3;
        size_t colm_size = 4;

        int **darr = malloc(line_size * sizeof(int **));

        for (int i = 0; i < line_size; i++)
                darr[i] = malloc(colm_size * sizeof(int));

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        darr[line][colm] = line + colm;
                }
        }

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        printf("%d\t", darr[line][colm]);
                }
                printf("\n");
        }

        if (darr != NULL) {
                for (int i = 0; i < line_size; i++) {
                        if (darr[i] != NULL) {
                                free(darr[i]);
                                darr[i] = NULL;
                        }
                }
                free(darr);
                darr = NULL;
        }
}

int main(int argc, char *argv[])
{
        static_2D_array();
        dynamic_2D_array();

        return EXIT_SUCCESS;
}
