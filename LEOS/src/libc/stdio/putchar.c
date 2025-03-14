#include <stdio.h>
#include <sys/cdefs.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ch) {
#if defined(__is_libk)    
    return tty_putc(ch);
#else
    // TODO libc sys calls
#endif
    return ch;
}