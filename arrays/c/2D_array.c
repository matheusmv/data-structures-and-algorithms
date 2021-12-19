#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void static_2D_array()
{
        int sarr[3][3] = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
        };

        uint line_size = sizeof(sarr) / sizeof(sarr[0]);
        uint colm_size = sizeof(sarr[0]) / sizeof(int);

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        printf("%d\t", sarr[line][colm]);
                }
                printf("\n");
        }
}

void dynamic_2D_array()
{
        uint line_size = 3;
        uint colm_size = 4;

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

static void *get_index(void **arr, size_t size, uint line, uint column)
{
        // return ((char *) arr[line]) + size * column;
        return *(((char **) arr) + line) + column * size;
}

void generic_dynamic_2D_array()
{
        uint line_size = 3;
        uint colm_size = 4;

        size_t type_size = sizeof(int);

        void **darr = malloc(line_size * sizeof(void **));

        for (int i = 0; i < line_size; i++) {
                darr[i] = malloc(colm_size * type_size);
        }

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        void *p = get_index(darr, type_size, line, colm);
                        int value = line + colm;
                        memmove(p, &value, type_size);
                }
        }

        for (int line = 0; line < line_size; line++) {
                for (int colm = 0; colm < colm_size; colm++) {
                        printf("%d\t", *(int *) get_index(darr, type_size, line, colm));
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
        generic_dynamic_2D_array();

        return EXIT_SUCCESS;
}
