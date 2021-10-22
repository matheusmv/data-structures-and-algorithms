#include <stdio.h>
#include <stdlib.h>

int nested_recursion(int number)
{
        if (number > 100) {
                return number - 10;
        }

        return nested_recursion(nested_recursion(number + 11));
}

int main(int argc, char *argv[])
{
        const int value = 95;

        printf("%d\n", nested_recursion(value)); /* 91 */

        return EXIT_SUCCESS;
}
