#include "base64.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error {
        ENCODE_INVALID_PARAMETERS,
        INVALID_BUFFER_SIZE,
        MALLOC_ERROR,
        DECODE_INVALID_PARAMETERS,
        DECODE_INVALID_INPUT,
};

static char *error_message[] = {
        "base64_encode() error: invalid parameters. (%s) (%ld) (%s) (%ld)\n",
        "%s error: buffer has size: %ld, required size: %ld\n",
        "malloc() error: (%s)\n",
        "base64_decode() error: invalid parameters. (%s) (%s) (%ld)\n",
        "base64_decode() error: invalid input. (%c) in (%s)\n",
};

static const char PAD = '=';

static char encode_table[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
        'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};

static char decode_table[] = {
        62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,
        -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27,
        28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
        46, 47, 48, 49, 50, 51
};

static size_t
stringlen_to_base64len(size_t string_length)
{
        size_t base64len = string_length;

        if (string_length % 3 != 0) {
                base64len += 3 - (string_length % 3);
        }

        return (base64len / 3) * 4;
}

static size_t
base64str_length(const char *b64string)
{
        assert(b64string != NULL);

        size_t length = (strlen(b64string) / 4) * 3;

        for (size_t i = length; i > 0; --i) {
                if (b64string[i] == PAD) {
                        length -= 1;
                }
        }

        return length;
}

static int
isvalidb64char(const char value)
{
        if (value >= '0' && value <= '9') {
                return 1;
        }

        if (value >= 'A' && value <= 'Z') {
                return 1;
        }

        if (value >= 'a' && value <= 'z') {
                return 1;
        }

        if (value == '+' || value == '/' || value == PAD) {
                return 1;
        }

        return 0;
}

int
base64_encode(const unsigned char *src, size_t length, char *dest, size_t size)
{
        if (src == NULL || length <= 0 || dest == NULL || size <= 0) {
                fprintf(stderr, error_message[ENCODE_INVALID_PARAMETERS], src, length, dest, size);
                return -1;
        }

        size_t src_b64len = stringlen_to_base64len(length);

        if (size < src_b64len) {
                fprintf(stderr, error_message[INVALID_BUFFER_SIZE], "base64_encode()", size, src_b64len);
                return -1;
        }

        char *base64_string = malloc((src_b64len + 1));
        if (base64_string == NULL) {
                fprintf(stderr, error_message[MALLOC_ERROR], strerror(errno));
                return -1;
        }

        base64_string[src_b64len] = '\0';

        for (size_t i = 0, j = 0; i < length; i += 3, j += 4) {
                size_t src_char = src[i];

                src_char = (i + 1 < length) ? (src_char << 8 | src[i + 1]) : (src_char << 8);
                src_char = (i + 2 < length) ? (src_char << 8 | src[i + 2]) : (src_char << 8);

                base64_string[j]     = encode_table[(src_char >> 18) & 0x3F];
                base64_string[j + 1] = encode_table[(src_char >> 12) & 0x3F];

                if (i + 1 < length) {
                        base64_string[j + 2] = encode_table[(src_char >> 6) & 0x3F];
                } else {
                        base64_string[j + 2] = PAD;
                }

                if (i + 2 < length) {
                        base64_string[j + 3] = encode_table[src_char & 0x3F];
                } else {
                        base64_string[j + 3] = PAD;
                }
        }

        memset(dest, 0, size);
        memmove(dest, base64_string, strlen(base64_string));
        free(base64_string);

        return 0;
}

int
base64_decode(const char *src, unsigned char *dest, size_t size)
{
        if (src == NULL || dest == NULL || size <= 0) {
                fprintf(stderr, error_message[DECODE_INVALID_PARAMETERS], src, dest, size);
                return -1;
        }

        size_t src_length = base64str_length(src);
        size_t src_total_length = strlen(src);
        if (size <  src_length|| src_total_length %4 != 0) {
                fprintf(stderr, error_message[INVALID_BUFFER_SIZE], "base64_decode()", src_length, size);
                return -1;
        }

        for (int i = 0; i < src_total_length; ++i) {
                if (!isvalidb64char(src[i])) {
                        fprintf(stderr, error_message[DECODE_INVALID_INPUT], src[i], src);
                        return -1;
                }
        }

        memset(dest, 0, size);

        for (int i = 0, j = 0; i < src_total_length; i += 4, j += 3) {
                size_t src_char = decode_table[src[i] - 43];

                src_char = (src_char << 6) | decode_table[src[i + 1] - 43];

                src_char = (src[i + 2] == PAD) ? (src_char << 6) : ((src_char << 6) | decode_table[src[i + 2] - 43]);
                src_char = (src[i + 3] == PAD) ? (src_char << 6) : ((src_char << 6) | decode_table[src[i + 3] - 43]);

                dest[j] = (src_char >> 16) & 0xFF;

                if (src[i + 2] != PAD) {
                        dest[j + 1] = (src_char >> 8) & 0xFF;
                }

                if (src[i + 3] != PAD) {
                        dest[j + 2] = src_char & 0xFF;
                }
        }

        return 0;
}
