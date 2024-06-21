// src/arch/i386/tty.c -- tty implementation for x86
#include <stdint.h>
#include "tty.h"

typedef struct {
	uint8_t fg_clr	: 4;
	uint8_t bg_clr	: 3;
	uint8_t blink		: 1;
} VGA_PARAMS;

VGA_PARAMS vga = {0xb, 0x0, 0x0};

void tty_print(const char* str) {
	volatile uint8_t* mem = (volatile uint8_t*)0xb8000;
	while (*str) {
		*mem++ = *str++;
		*mem++ = *(uint8_t*)&vga;
	}
}		
