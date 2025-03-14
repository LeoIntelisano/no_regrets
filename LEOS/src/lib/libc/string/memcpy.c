#include <libc/string.h>

void* memcpy(void* __restrict dest, const void* __restrict src, size_t n) {
    unsigned char* d = (unsigned char*) dest;
    const unsigned char* s = (unsigned char*) src;

    while (n) {
        *d++ = *s++;
        n--;
    }
    return dest;
}