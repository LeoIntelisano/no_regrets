#ifndef VGA_H
#define VGA_H
#include <stdint.h>

// General VGA driver. Right now only focussed on writing to cursor position

// returns 1 on fail
int vga_update_cursor(uint16_t index);


#endif // VGA_H