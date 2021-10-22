#include <stdio.h>
#include <stdlib.h>

int recursive_sum(int number)
{
        if (number < 0)
                return -1;

        if (number == 0)
                return 0;

        return recursive_sum(number - 1) + number;
}

int loop_sum(int number)
{
        if (number < 0)
                return -1;

        int sum = 0;

        while (number > 0)
                sum += number--;

        return sum;
}

int sum(int number)
{
        if (number < 0)
                return -1;

        return number * (number + 1) / 2;
}

int main(int argc, char *argv[])
{
        const int value = 7;

        printf("%d\n", recursive_sum(value)); /* 28 */
        printf("%d\n", loop_sum(value));      /* 28 */
        printf("%d\n", sum(value));           /* 28 */

        return EXIT_SUCCESS;
}
