#ifndef TERM_H
#define TERM_H

// Abstracted terminal interface

typedef enum TERM_COLORS_ENUM {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GRAY, 
    DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGH_RED, PINK, YELLOW, WHITE
}TERM_COLORS;

typedef struct {
    void (*init)(void);
    void (*clear)(void);
    int (*putchar)(int);
    void (*print)(const char* str);
    void (*set_color)(const TERM_COLORS, const TERM_COLORS);
    TERM_COLORS (*get_fg_color)(void);
    TERM_COLORS (*get_bg_color)(void);
} K_TERMINAL;

extern K_TERMINAL tty_term;

#endif // TERM_H