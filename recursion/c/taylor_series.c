#include <stdio.h>
#include <stdlib.h>

double e(int exponent, int nterms)
{
        static double exp = 1;
        static double fac = 1;
        double result = 0;

        if (nterms == 0)
                return 1;

        result = e(exponent, nterms - 1);
        exp *= exponent;
        fac *= nterms;

        return result + exp / fac;
}

double e_horner(int exponent, int nterms)
{
        static double sum;

        if (nterms == 0)
                return sum;

        sum = 1 + exponent * sum / nterms;

        return e_horner(exponent, nterms - 1);
}

double e_loop(int exponent, int nterms)
{
        double sum = 1;
        double num = 1;
        double den = 1;

        for (int i = 1; i <= nterms; i++) {
                num *= exponent;
                den *= i;
                sum += num / den;
        }

        return sum;
}

int main(int argc, char *argv[])
{
        printf("%f\n", e(1, 10));        /* 2.718282 */
        printf("%f\n", e_horner(1, 10)); /* 2.718282 */
        printf("%f\n", e_loop(1, 10));   /* 2.718282 */

        return EXIT_SUCCESS;
}
