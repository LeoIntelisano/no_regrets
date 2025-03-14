// src/include/tty/tty.h -- arch independent tty interface
#ifndef TTY_H
#define TTY_H
#include <stdint.h>

/* prints n characters to tty hardware */
void tty_print(const char*);
int tty_putc(int);
/* fills tty buffer with 0s... clears screen */
void tty_clear();

/* test function to print A-Z to fill entire buffer */

void tty_test();
void tty_test_row();
void tty_test_1_left();


// Sets attribute bits: [7] blink, [6:4] bg color, [3:0] fg color
void tty_set_attr(uint8_t attr);
#endif	// TTY_H
