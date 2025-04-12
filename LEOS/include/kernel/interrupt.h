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

typedef struct {
    uint32_t old_edi;
    uint32_t old_esi;
    uint32_t old_ebp;
    uint32_t old_esp;
    uint32_t old_ebx;
    uint32_t old_edx;
    uint32_t old_ecx;
    uint32_t old_eax;

    uint32_t isr_num;   // although could fit in uint8_t, 
                        // not trying to deal with internal compiler padding
    uint32_t err;
    uint32_t old_eip;
    uint32_t old_cs;
    uint32_t old_eflags;
} __attribute__((__packed__)) isr_frame;

extern idt_t idt[MAX_INTERRUPTS]; 
extern idt_descr_t idt_descr;
// takes an error code
void pg_handler(uint32_t);
void set_idt_entry(int vec, void* isr, uint16_t selector, uint8_t flags);
void load_idt();
void sys_isr_disp(isr_frame proc_ss);
void idt_init();
#endif