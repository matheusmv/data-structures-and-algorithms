#include <stdio.h>
#include <stdlib.h>

int ncr_recursive(int nelem, int nperm)
{
        if (nelem < 0 || nperm < 0)
                return -1;

        if (nperm == 0 || nelem == nperm)
                return 1;

        return ncr_recursive(nelem - 1, nperm - 1) + ncr_recursive(nelem - 1, nperm);
}

int factorial(int);

int ncr(int nelem, int nperm)
{
        if (nelem < 0 || nperm < 0)
                return -1;

        return factorial(nelem) / (factorial(nperm) * factorial(nelem - nperm));
}

int main(int argc, char *argv[])
{
        const int nelem = 5, nperm = 3;

        printf("%d\n", ncr_recursive(nelem, nperm)); /* 10 */
        printf("%d\n", ncr(nelem, nperm));           /* 10 */

        return EXIT_SUCCESS;
}

int factorial(int number)
{
        if (number < 0)
                return -1;

        int result = 1;

        while (number > 0)
                result *= number--;

        return result;
}
