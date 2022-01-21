#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

long long recursive_fib(long long nnumber)
{
        if (nnumber < 0)
                return -1;

        if (nnumber <= 1)
                return nnumber;

        return recursive_fib(nnumber - 2) + recursive_fib(nnumber - 1);
}

long long loop_fib(int nnumber)
{
        if (nnumber < 0)
                return -1;

        if (nnumber <= 1)
                return nnumber;

        long long arr[nnumber];
        arr[0] = 0;
        arr[1] = 1;

        for (long long i = 2; i <= nnumber; i++)
                arr[i] = arr[i - 1] + arr[i - 2];

        return arr[nnumber];
}

static long long cache[10000];

long long memo_fib(int nnumber)
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
        const int position = 35;

        struct timeval  tv1, tv2;

        gettimeofday(&tv1, NULL);
        printf("%lld\n", recursive_fib(position));      /* 9227465 */
        gettimeofday(&tv2, NULL);

        printf("Total time = %f seconds\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double) (tv2.tv_sec - tv1.tv_sec));

        gettimeofday(&tv1, NULL);
        printf("%lld\n", loop_fib(position));           /* 9227465 */
        gettimeofday(&tv2, NULL);

        printf("Total time = %f seconds\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double) (tv2.tv_sec - tv1.tv_sec));

        memset(cache, -1, sizeof(cache));

        gettimeofday(&tv1, NULL);
        printf("%lld\n", memo_fib(position));           /* 9227465 */
        gettimeofday(&tv2, NULL);

        printf("Total time = %f seconds\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double) (tv2.tv_sec - tv1.tv_sec));

        return EXIT_SUCCESS;
}
