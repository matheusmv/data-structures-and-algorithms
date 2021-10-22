#include <stdio.h>
#include <stdlib.h>

void head_recursion(int number)
{
        if (number > 0) {
                head_recursion(number - 1);
                printf("%d\n", number);
        }
}

void loop_operation(int number)
{
        int i = 1;

        while (i <= number) {
                printf("%d\n", i);
                i++;
        }
}

int main(int argc, char *argv[])
{
        const int value = 3;

        head_recursion(value); /* 1 2 3 */
        loop_operation(value); /* 1 2 3 */

        return EXIT_SUCCESS;
}
