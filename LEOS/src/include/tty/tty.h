// src/include/tty/tty.h -- arch independent tty interface
#ifndef TTY_H
#define TTY_H
#include <stdint.h>

/* prints n characters to tty hardware */
void tty_print(const char*);

/* fills tty buffer with 0s... clears screen */
void tty_clear();

/* test function to print A-Z to fill entire buffer */
void tty_test();

#endif	// TTY_H
