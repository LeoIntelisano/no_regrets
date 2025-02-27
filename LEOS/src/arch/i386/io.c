#include "io/io.h"

/*write 1 byte, 1 word */
void outb(uint16_t loc, uint8_t src) {
    asm("outb %1, %0": : "dN"(loc), "a"(src));
}
void outw(uint16_t loc, uint16_t src) {
    asm("outw %1, %0": : "dN"(loc), "a"(src));
}


/* read 1 byte, 1 word */
uint8_t inb(uint16_t loc) {
    uint8_t r;
    asm("inb %1, %0": "=a"(r): "d"(loc));
    return r;
}
uint16_t inw(uint16_t loc) {
    uint16_t r;
    asm("inw %1, %0": "=a"(r): "d"(loc));
    return r;
}

uint8_t _test_asm() {
    uint8_t r = 1;
    uint8_t inc = 3;
    asm("addb %1, %0": "+a"(r): "g"(inc));
    // r should = 4
    return r;
}