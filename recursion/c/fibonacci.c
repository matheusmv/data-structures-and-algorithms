#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recursive_fib(int nnumber)
{
        if (nnumber < 0)
                return -1;

        if (nnumber <= 1)
                return nnumber;

        return recursive_fib(nnumber - 2) + recursive_fib(nnumber - 1);
}

int loop_fib(int nnumber)
{
        if (nnumber < 0)
                return -1;

        if (nnumber <= 1)
                return nnumber;

        int prev = 0, next = 1;

        for (int total = 2; total <= nnumber; total++) {
                int aux = prev;
                prev = next;
                next = aux + prev;
        }

        return next;
}

int cache[100];

int memo_fib(int nnumber)
{
        if (nnumber < 0)
                return -1;

        if (nnumber <= 1) {
                cache[nnumber] = nnumber;
                return nnumber;
        }

        if (cache[nnumber - 2] == -1)
                cache[nnumber - 2] = memo_fib(nnumber - 2);

        if (cache[nnumber - 1] == -1)
                cache[nnumber - 1] = memo_fib(nnumber - 1);

        cache[nnumber] = cache[nnumber - 2] + cache[nnumber - 1];

        return cache[nnumber - 2] + cache[nnumber - 1];
}

int main(int argc, char *argv[])
{
        const int position = 10;

        printf("%d\n", recursive_fib(position)); /* 55 */
        printf("%d\n", loop_fib(position));      /* 55 */

        memset(cache, -1, sizeof(cache));

        printf("%d\n", memo_fib(position));      /* 55 */

        return EXIT_SUCCESS;
}
