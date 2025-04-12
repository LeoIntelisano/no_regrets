#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#define MAX_INTERRUPTS 256U
#define PF_VEC 14

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offset_high;
}  __attribute__((__packed__)) idt_t;

typedef struct {
    uint16_t size;
	uint32_t base_addr;
} __attribute__((__packed__)) idt_descr_t; 

extern idt_t idt[MAX_INTERRUPTS]; 
extern idt_descr_t idt_descr;
// takes an error code
void pg_handler(uint32_t);
void set_idt_entry(int vec, void* isr, uint16_t selector, uint8_t flags);
void load_idt();
#endif