#include <string.h>
#include <stddef.h>

void* memset(void* dest, int ch, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    while (n) {
        *d++ = (unsigned char)ch;
    }
    return dest;
}