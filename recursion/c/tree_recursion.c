#include <stdio.h>
#include <stdlib.h>

void tree_recursion_v1(int number)
{
        if (number > 0) {
                printf("%d ", number);
                tree_recursion_v1(number - 1);
                tree_recursion_v1(number - 1);
        }
}

void tree_recursion_v2(int number)
{
        if (number > 0) {
                tree_recursion_v2(number - 1);
                printf("%d ", number);
                tree_recursion_v2(number - 1);
        }
}

void tree_recursion_v3(int number)
{
        if (number > 0) {
                tree_recursion_v3(number - 1);
                tree_recursion_v3(number - 1);
                printf("%d ", number);
        }
}

int main(int argc, char *argv[])
{
        const int value = 3;

        tree_recursion_v1(value); /* 3 2 1 1 2 1 1 */
        printf("\n");

        tree_recursion_v2(value); /* 1 2 1 3 1 2 1 */
        printf("\n");

        tree_recursion_v3(value); /* 1 1 2 1 1 2 3 */
        printf("\n");

        return EXIT_SUCCESS;
}
