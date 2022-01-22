#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main(void) {
        const char *data = "Hello World in Base64";

        char encoded_data[1024];
        char decoded_data[1024];

        int status = 0;

        status = base64_encode((unsigned char *) data, strlen(data), encoded_data, 1024);
        if (status < 0) {
                return EXIT_FAILURE;
        }

        status = base64_decode(encoded_data, (unsigned char *) decoded_data, 1024);
        if (status < 0) {
                return EXIT_FAILURE;
        }

        printf("original: %s\n", data);
        printf("base64 encoded: %s\n", encoded_data);
        printf("base64 decoded: %s\n", decoded_data);

        return EXIT_SUCCESS;
}
