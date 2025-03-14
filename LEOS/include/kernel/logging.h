#ifndef LOGGING_H
#define LOGGING_H

#include <kernel/term.h>

// if K_TERMINAL is null, use printf
void k_panic(K_TERMINAL*, const char* , ...);
void k_warn(K_TERMINAL*, const char*, ...);
void k_info(K_TERMINAL*, const char*, ...);


#endif // LOGGING_H