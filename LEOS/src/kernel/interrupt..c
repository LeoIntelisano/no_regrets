#include <kernel/interrupt.h>
#include <stdio.h>

void pg_handler(uint32_t err) {
    printf("EXCEPTION: PAGE FAULT\n");
    while (1) asm volatile ("cli \n hlt");
}