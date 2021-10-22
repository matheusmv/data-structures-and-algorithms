#include <stdio.h>
#include <stdlib.h>

void toh(int nelem, int a, int b, int c)
{
        if (nelem > 0) {
                toh(nelem - 1, a, c, b);
                printf("move %d to %d\n", a, c);
                toh(nelem - 1, b, a, c);
        }
}

int main(int argc, char *argv[])
{
        toh(3, 1, 2, 3);

        return EXIT_SUCCESS;
}
