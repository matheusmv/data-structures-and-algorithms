#include <stdio.h>
#include <stdlib.h>

u_long get_address(u_long base_addr, u_int blck, u_int row, u_int colm, u_int nrow, u_int ncolm, size_t data_size)
{
        return base_addr + (blck * nrow * ncolm + row * ncolm + colm) * data_size;
}

int main()
{
        int arr[3][3][3] = {
                {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}},
                {{4, 5, 6}, {4, 5, 6}, {4, 5, 6}},
                {{7, 8, 9}, {7, 8, 9}, {7, 8, 9}},
        };

        u_long base_addr = (u_long) &arr[0][0];
        size_t nbytes = sizeof(arr[0][0][0]);

        u_int block = 0;
        u_int row = 0;
        u_int colm = 1;
        u_int nrow = sizeof(arr[0]) / sizeof(arr[0][0]);
        u_int ncolm = sizeof(arr[0][0]) / sizeof(int);

        u_long result = get_address(base_addr, block, row, colm, nrow, ncolm, nbytes);

        printf("base address: %p\n", base_addr);
        printf("address of element at index [%d][%d][%d]: %p\n", block, row, colm, result);

        return EXIT_SUCCESS;
}
