#include <libc/stdio.h>
#include <kernel/tty.h>

int puts(const char* src) {
    return printf("%s\n", src);
}
