#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

int base64_encode(const unsigned char *src, size_t length, char *dest, size_t size);
int base64_decode(const char *src, unsigned char *dest, size_t size);

#endif
