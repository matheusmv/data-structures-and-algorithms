#include <stdio.h>
#include <stdlib.h>

float recursive_exponentiation_v1(int base, int exponent)
{
        if (exponent >= 0) {
                if (exponent == 0)
                        return 1;

                return recursive_exponentiation_v1(base, (exponent - 1)) * base;
        }

        exponent = -exponent;

        if (exponent == 0)
                return 1;

        return 1 / (recursive_exponentiation_v1(base, (exponent - 1)) * base);
}

float recursive_exponentiation_v2(int base, int exponent)
{
        if (exponent >= 0) {
                if (exponent == 0)
                        return 1;

                if (exponent % 2 == 0)
                        return recursive_exponentiation_v2(base * base, (exponent / 2));

                return recursive_exponentiation_v2(base * base, (exponent - 1) / 2) * base;
        }

        exponent = -exponent;

        if (exponent == 0)
                return 1;

        if (exponent % 2 == 0)
                return 1 / (recursive_exponentiation_v2(base * base, (exponent / 2)));

        return 1 / (recursive_exponentiation_v2(base * base, (exponent - 1) / 2) * base);
}

float loop_exponentiation_v1(int base, int exponent)
{
        float result = 1;

        if (exponent >= 0) {
                for (int i = 0; i < exponent; i++) {
                        result *= base;
                }

                return result;
        }

        exponent = -exponent;

        for (int i = 0; i < exponent; i++) {
                result *= base;
        }

        return 1 / result;
}

float loop_exponentiation_v2(int base, int exponent)
{
        float aux = 1;

        if (exponent >= 0) {
                while (exponent > 1) {
                        if (exponent % 2 == 0) {
                                base *= base;
                        } else {
                                aux *= base;
                                base *= base;
                        }
                        exponent /= 2;
                }

                base *= aux;

                return base;
        }

        exponent = -exponent;

        while (exponent > 1) {
                if (exponent % 2 == 0) {
                        base *= base;
                } else {
                        aux *= base;
                        base *= base;
                }
                exponent /= 2;
        }

        base *= aux;

        return 1 / (float) base;
}

int main(int argc, char *argv[])
{
        const int base = 2, exponent = 10;

        printf("%.4f\n", recursive_exponentiation_v1(base, exponent)); /* 1024 */
        printf("%.4f\n", recursive_exponentiation_v2(base, exponent)); /* 1024 */
        printf("%.4f\n", loop_exponentiation_v1(base, exponent));      /* 1024 */
        printf("%.4f\n", loop_exponentiation_v2(base, exponent));      /* 1024 */

        return EXIT_SUCCESS;
}
