#include <stdio.h>
#include <stdlib.h>

void static_3D_array()
{
        int sarr[3][3][3] = {
                {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}},
                {{4, 5, 6}, {4, 5, 6}, {4, 5, 6}},
                {{7, 8, 9}, {7, 8, 9}, {7, 8, 9}},
        };

        size_t block_size = sizeof(sarr) / sizeof(sarr[0]);
        size_t line_size = sizeof(sarr[0]) / sizeof(sarr[0][0]);
        size_t colm_size = sizeof(sarr[0][0]) / sizeof(int);

        for (int block = 0; block < block_size; block++) {
                printf("%d\n", block);
                for (int line = 0; line < line_size; line++) {
                        printf("\n");
                        for (int colm = 0; colm < colm_size; colm++) {
                                printf("\t%d", sarr[block][line][colm]);
                        }
                }
                printf("\n\n");
        }
}

void dynamic_3D_array()
{
        size_t block_size = 3;
        size_t line_size = 4;
        size_t colm_size = 4;

        int ***darr = malloc(block_size * sizeof(int ***));

        for (int block = 0; block < block_size; block++) {
                darr[block] = malloc(line_size * sizeof(int **));
                for (int line = 0; line < line_size; line++) {
                        darr[block][line] = malloc(colm_size * sizeof(int));
                }
        }

        for (int block = 0; block < block_size; block++) {
                for (int line = 0; line < line_size; line++) {
                        for (int colm = 0; colm < line_size; colm++) {
                                darr[block][line][colm] = block + line + colm;
                        }
                }
        }

        for (int block = 0; block < block_size; block++) {
                printf("%d\n", block);
                for (int line = 0; line < line_size; line++) {
                        printf("\n");
                        for (int colm = 0; colm < line_size; colm++) {
                                printf("\t%d", darr[block][line][colm]);
                        }
                }
                printf("\n\n");
        }

        if (darr != NULL) {
                for (int block = 0; block < block_size; block++) {
                        for (int line = 0; line < line_size; line++) {
                                if (darr[block][line] != NULL) {
                                        free(darr[block][line]);
                                        darr[block][line] = NULL;
                                }
                        }
                        if (darr[block] != NULL) {
                                free(darr[block]);
                                darr[block] = NULL;
                        }
                }
                free(darr);
                darr = NULL;
        }
}

int main(int argc, char *argv[])
{
        static_3D_array();
        dynamic_3D_array();

        return EXIT_SUCCESS;
}
