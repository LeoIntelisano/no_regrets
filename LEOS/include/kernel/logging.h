#ifndef LOGGING_H
#define LOGGING_H
#include <kernel/term.h>

#define MAX_PRINT_STREAM 256

// if K_TERMINAL is null, use printf
void k_printf(K_TERMINAL*, const char* __restrict , ...);
void k_panic(K_TERMINAL*, const char* __restrict , ...);
void k_warn(K_TERMINAL*, const char* __restrict, ...);
void k_info(K_TERMINAL*, const char* __restrict, ...);


#endif // LOGGING_H