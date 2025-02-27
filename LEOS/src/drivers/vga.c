#include "drivers/vga.h"
#include "io/io.h"

// VGA IO port
#define VGA_ADDR 0x3D4
#define VGA_DATAR 0x3D5

// VGA cursor position registers index
#define VGA_CURS_HIGHR 0xE
#define VGA_CURS_LOWR 0xF


// returns contents of a CRT register
// param: index: VGA CRT Register index http://www.osdever.net/FreeVGA/vga/crtcreg.htm
uint8_t vga_crt_read(uint8_t index) {
    uint8_t old_index  = inb(VGA_ADDR);
    outb(VGA_ADDR, index);
    uint8_t reg_contents = inb(VGA_DATAR);
    outb(VGA_ADDR, old_index);
    return reg_contents;
}

// writes 8 bits to CRT register at index
// suggestion is to read first and only change bits necessary before writing
void vga_crt_write(uint8_t index, uint8_t src) {
    uint8_t old_index  = inb(VGA_ADDR);
    outb(VGA_ADDR, index);
    outb(VGA_DATAR, src);
    outb(VGA_ADDR, old_index);
}


int vga_update_cursor(uint16_t index) {
    uint16_t old_curs_pos = vga_crt_read(VGA_CURS_HIGHR) << 8 | vga_crt_read(VGA_CURS_LOWR);
    if (old_curs_pos == index)
        return 0;

    vga_crt_write(VGA_CURS_HIGHR, (index >> 8) & 0xFF);
    vga_crt_write(VGA_CURS_LOWR, index & 0xFF);

    uint16_t new_curs_pos = vga_crt_read(VGA_CURS_HIGHR) << 8 | vga_crt_read(VGA_CURS_LOWR);
    if (new_curs_pos != index)
        return -1;
    return 0;
}