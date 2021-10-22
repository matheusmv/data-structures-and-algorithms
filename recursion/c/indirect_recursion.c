#include <stdio.h>
#include <stdlib.h>

int function_a(int);
int function_b(int);

int function_a(int number)
{
        if (number > 0) {
                printf("%d ", number);
                function_b(number - 1);
        }
}

int function_b(int number)
{
        if (number > 1) {
                printf("%d ", number);
                function_a(number / 2);
        }
}

int main(int argc, char *argv[])
{
        const int value = 20;

        function_a(value); /* 20 19 9 8 4 3 1 */
        printf("\n");

        function_b(value); /* 20 10 9 4 3 1 */
        printf("\n");

        return EXIT_SUCCESS;
}
