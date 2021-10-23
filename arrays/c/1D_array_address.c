#include <stdio.h>
#include <stdlib.h>

u_long get_address(u_long base_addr, u_int index, size_t data_size)
{
        return base_addr + index * data_size;
}

int main()
{
        int arr[5] = { 3, 5, 8, 4, 2 };

        u_long base_addr = (u_long) &arr[0];
        size_t nbytes = sizeof(arr[0]);

        u_int index = 3;
        u_long result = get_address(base_addr, index, nbytes);

        printf("base address: %p\n", base_addr);
        printf("address of element at index [%d]: %p\n", index, result);

        return EXIT_SUCCESS;
}
