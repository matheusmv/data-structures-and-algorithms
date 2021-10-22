#include <stdio.h>
#include <stdlib.h>

void tail_recursion(int number)
{
        if (number > 0) {
                printf("%d\n", number);
                tail_recursion(number - 1);
        }
}

void loop_operation(int number)
{
        while (number > 0) {
                printf("%d\n", number);
                number--;
        }
}

int main(int argc, char *argv[])
{
        const int value = 3;

        tail_recursion(value); /* 3 2 1 */
        loop_operation(value); /* 3 2 1 */

        return EXIT_SUCCESS;
}
