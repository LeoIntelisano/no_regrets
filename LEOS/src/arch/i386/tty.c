// src/arch/i386/tty.c -- tty implementation for x86
#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <drivers/vga.h>

#define index(x,y)((x+VGA_WIDTH*y)*2)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25


typedef struct {
	uint8_t fg_clr  : 4;
	uint8_t bg_clr  : 3;
	uint8_t blink   : 1;
} vga_t;

// consider using static for these globals

// holds row and collumn values where next char will be written
size_t tty_row = 0;
size_t tty_col = 0;


vga_t vga = {0x5, 0x0, 0x0};

volatile uint8_t* vga_mem = (volatile uint8_t*)0xb8000;


static void tty_set_cursor(size_t x, size_t y) {
	vga_set_cursor(index(x,y)/2);
}

static void tty_clear_r(size_t r){
	for (size_t i = 0; i < VGA_WIDTH; i++) {
		vga_mem[index(i, r)] = ' ';
		vga_mem[index(i, r)+1] = *(uint8_t*)&vga;
	}
}

static void tty_putc_at(int ch, size_t x, size_t y){
	*(volatile uint16_t*)&vga_mem[index(x, y)] =  (uint8_t)ch | (*(uint8_t*)&vga) << 8;
}

static void tty_scroll(){
	for (size_t r = 1; r < VGA_HEIGHT; r++){
		for (size_t c = 0; c < VGA_WIDTH; c++) {
			tty_putc_at(vga_mem[index(c, r)], c, r-1);
		}
	}
	tty_clear_r(VGA_HEIGHT-1);
	tty_row = VGA_HEIGHT-1;
	tty_col = 0;
}
int tty_putc(int ch) {	
	// format checks #TODO Add other special character checks 
	if (ch == '\n'){
		tty_row++;
		tty_col = 0;
		tty_set_cursor(tty_col % VGA_WIDTH, tty_row % VGA_HEIGHT);
		return '\n';
	}
	if (ch == '\t'){
		tty_col = (tty_col + (4 - tty_col%4)) % VGA_WIDTH;
		tty_set_cursor(tty_col % VGA_WIDTH, tty_row % VGA_HEIGHT);
		return '\t';
	}
	tty_putc_at(ch, tty_col, tty_row);
	tty_col++;
	
	if (tty_col >= VGA_WIDTH) {
		tty_col = 0;
		tty_row++;
	}

	if (tty_row >= VGA_HEIGHT) {
		tty_scroll();
	}

	if (vga_mem[index((tty_col)%VGA_WIDTH, tty_row)] == (uint8_t)' ')
		vga_mem[index((tty_col)%VGA_WIDTH, tty_row) + 1] = *(uint8_t*)&vga;

	tty_set_cursor(tty_col % VGA_WIDTH, tty_row % VGA_HEIGHT);
	return ch;
}

void tty_test(){
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i+=2) {
        tty_putc('A' + (i / 2) % 26);  // Characters A-Z in a loop
    }
}
void tty_test_1_left(){
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2 - 2; i+=2) {
        tty_putc('A' + (i / 2) % 26);  // Characters A-Z in a loop
    }
}
void tty_test_row() {
	for (size_t i = 0; i < VGA_WIDTH*2; i+=2) {
		tty_putc('A' + (i / 2) % 26);
	}
}
void tty_print(const char* str) {
	while (*str) {
		tty_putc(*str++);
	}
}		

static void tty_top() {
	vga_mem = (volatile uint8_t*)0xb8000;
}

void tty_clear() {
	tty_top();
	for (size_t i = 0; i < VGA_HEIGHT; i++){
		tty_clear_r(i);
	}
	vga_set_cursor(0);
}

void tty_set_attr(uint8_t attr) {
	*(uint8_t*)&vga = attr;
	if (vga_mem[index((tty_col)%VGA_WIDTH, tty_row)] == (uint8_t)' ')
		vga_mem[index((tty_col)%VGA_WIDTH, tty_row) + 1] = *(uint8_t*)&vga;
}
void tty_set_color(uint8_t fg, uint8_t bg) {
	tty_set_attr((fg & 0xF) | ((bg & 7) << 4));
}

uint8_t tty_get_attr() {
	return *(uint8_t*)&vga;
}