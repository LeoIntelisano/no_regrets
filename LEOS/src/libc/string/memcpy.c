#include <libc/string.h>

void* memcpy(void* __restrict dest, const void* __restrict src, size_t n) {
    unsigned char* d = (unsigned char*) dest;
    const unsigned char* s = (const unsigned char*) src;

    for (size_t i = 0; i < n; i++)
			d[i] = s[i];
    return d;
}