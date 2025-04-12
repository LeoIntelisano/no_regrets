#include <kernel/interrupt.h>
#include <stdio.h>

#define INT_FLAGS 0xef
#define KERNEL_CODE_SEG 0x8

extern void (*isr_table[])(void); 

void pg_handler(uint32_t err) {
    (void)err;
    printf("EXCEPTION: PAGE FAULT\n");
    //while (1) asm volatile ("cli \n hlt");
}

void set_idt_entry(int vec, void* isr, uint16_t selector, uint8_t flags) {
    uint32_t addr = (uint32_t)isr;
    idt[vec].offset_low = addr & 0xFFFF;
    idt[vec].selector = selector;
    idt[vec].reserved = 0;
    idt[vec].flags = flags;
    idt[vec].offset_high = (addr >> 16) & 0xFFFF;
}

void idt_init() {
    for (int i = 0; i < MAX_INTERRUPTS; i++) {
        set_idt_entry(i, isr_table[i], KERNEL_CODE_SEG, INT_FLAGS);
    }
    load_idt();
}

void load_idt()  {
    idt_descr.base_addr = (uint32_t)idt;
    idt_descr.size = sizeof(idt) - 1;
    __asm__ volatile ("lidt (%0)" :: "r"(&idt_descr));
}

void sys_isr_disp(isr_frame proc_ss) {
    if (proc_ss.isr_num == PF_VEC) {
        pg_handler(proc_ss.err);
    }
    if (proc_ss.isr_num == 0xd) {
        printf("General Protection Fault\n");
    }
} 