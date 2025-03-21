#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdarg.h>
#include <stddef.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int vprintf(const char* __restrict, va_list);
int vsnprintf(char*, size_t, const char* __restrict, va_list);
int putchar(int);
int puts(const char*);
char* itoa(int, char*, int);

#ifdef __cplusplus
}
#endif
#endif