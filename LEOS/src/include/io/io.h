#ifndef IO_H
#define IO_H
#include <stdint.h>

/* Generalized IO wrappers for communication with peripherals */

/*write 1 byte, 1 word */
void outb(uint16_t loc, uint8_t src);
void outw(uint16_t loc, uint16_t src);


/* read 1 byte, 1 word */
uint8_t inb(uint16_t loc);
uint16_t inw(uint16_t loc);

uint8_t _test_asm(); 

#endif // IO_H