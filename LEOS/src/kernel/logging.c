#include <kernel/logging.h>
#include <kernel/term.h>
#include <stdio.h>
#include <stdarg.h>

//TODO

static void k_print(K_TERMINAL* term, const char* format, va_list args) {
    char buffer[MAX_PRINT_STREAM];
    vsnprintf(buffer, sizeof(buffer), format, args);
    term->print(buffer);
}

void k_printf(K_TERMINAL* term, const char* __restrict format, ...) {
    va_list args;
    va_start(args, format);
    
    if (!term) {
        vprintf(format, args);
        va_end(args);
        return;
    }
    k_print(term, format, args);
    va_end(args);
}

void k_panic(K_TERMINAL* term, const char* __restrict format, ...) {
    va_list args;
    va_start(args, format);
    const char* p = "[PANIC]\t";

    if (!term) {
        printf("%s", p);
        vprintf(format, args);
        va_end(args);
        return;
    }

    TERM_COLORS fg = term->get_fg_color();
    TERM_COLORS bg = term->get_bg_color();

    term->set_color(RED, BLACK);
    term->print(p);
    term->set_color(fg, bg);
    k_print(term, format, args);
    va_end(args);
}


void k_warn(K_TERMINAL* term, const char* __restrict format, ...) {
    va_list args;
    va_start(args, format);
    const char* p = "[WARN]\t";

    if (!term) {
        printf("%s", p);
        vprintf(format, args);
        va_end(args);
        return;
    }

    TERM_COLORS fg = term->get_fg_color();
    TERM_COLORS bg = term->get_bg_color();
    
    term->set_color(YELLOW, BLACK);
    term->print(p);
    term->set_color(fg, bg);
    k_print(term, format, args);
    va_end(args);
}
void k_info(K_TERMINAL* term, const char* __restrict format, ...) {
    va_list args;
    va_start(args, format);
    const char* p = "[INFO]\t";

    if (!term) {
        printf("%s", p);
        vprintf(format, args);
        va_end(args);
        return;
    }

    TERM_COLORS fg = term->get_fg_color();
    TERM_COLORS bg = term->get_bg_color();
    
    term->set_color(GREEN, BLACK);
    term->print(p);
    term->set_color(fg, bg);
    k_print(term, format, args);
    va_end(args);
}
