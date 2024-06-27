// src/arch/i386/tty.c -- tty implementation for x86
#include <stdint.h>
#include <stddef.h>
#include "tty/tty.h"

#define index(x,y)((x+VGA_WIDTH*y)*2)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef struct {
	uint8_t fg_clr  : 4;
	uint8_t bg_clr  : 3;
	uint8_t blink   : 1;
} vga_t;

size_t tty_row = 0;
size_t tty_col = 0;


vga_t vga = {0xb, 0x0, 0x0};
volatile uint8_t* vga_mem = (volatile uint8_t*)0xb8000;

int tty_putc(int ch) {	
	if (tty_col >= VGA_WIDTH) {
		tty_col = 0;
		tty_row++;
	}
	if (tty_row >= VGA_HEIGHT) {
		tty_row = 0;	
	}

	*(volatile uint16_t*)&vga_mem[index(tty_col++, tty_row)] =  (uint8_t)ch | (*(uint8_t*)&vga) << 8;
	return ch;
}

void tty_test(){
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i+=2) {
        tty_putc('A' + (i / 2) % 26);  // Characters A-Z in a loop
    }
}

void tty_print(const char* str) {
	while (*str) {
		tty_putc(*str++);
	}
	tty_row++;
	tty_col = 0;
}		

static void tty_top() {
	vga_mem = (volatile uint8_t*)0xb8000;
}

void tty_clear() {
	tty_top();
	for (size_t i = 0; i < 2*VGA_WIDTH*VGA_HEIGHT; i++){
		vga_mem[i++] = ' ';
		vga_mem[i] = *(uint8_t*)&vga;
	}
}

