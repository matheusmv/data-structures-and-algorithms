#include <stdio.h>
#include <stdlib.h>

int recursive_factorial(int number)
{
        if (number < 0)
                return -1;

        if (number <= 0)
                return 1;

        return recursive_factorial(number - 1) * number;
}

int loop_factorial(int number)
{
        if (number < 0)
                return -1;

        int result = 1;

        while (number > 0)
                result *= number--;

        return result;
}

int main(int argc, char *argv[])
{
        const int value = 5;

        printf("%d\n", recursive_factorial(value)); /* 120 */
        printf("%d\n", loop_factorial(value));      /* 120 */

        return EXIT_SUCCESS;
}
