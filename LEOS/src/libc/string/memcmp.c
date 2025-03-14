#include <libc/string.h>
#include <stddef.h>

int memcmp(const void* src1, const void* src2, size_t n) {
    const unsigned char* l = (const unsigned char*)src1;
    const unsigned char* r = (const unsigned char*)src2;

    for (size_t i = 0; i < n; i++) {
        if (l[i] < r[i])
            return -1;
        else if (r[i] < l [i])
            return 1;
    }
    return 0;
}