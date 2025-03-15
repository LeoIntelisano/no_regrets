#include <kernel/term.h>
#include <kernel/tty.h>
#include <stddef.h>

void tty_term_set_color(TERM_COLORS fg, TERM_COLORS bg) {
    tty_set_color((uint8_t)fg, (uint8_t)bg);
}

void tty_term_init() {
    tty_term_set_color(LIGHT_GRAY, BLACK);
    tty_clear();
}

TERM_COLORS tty_term_get_fg() {
    return (TERM_COLORS)(tty_get_attr() & 0xF);
}
TERM_COLORS tty_term_get_bg() {
    return (TERM_COLORS)((tty_get_attr() >> 4) & 7);
}

K_TERMINAL tty_term = {
    .init = tty_term_init,
    .clear = tty_clear,
    .putchar = tty_putc,
    .print = tty_print,
    .set_color = tty_term_set_color,
    .get_fg_color = tty_term_get_fg,
    .get_bg_color = tty_term_get_bg
};

