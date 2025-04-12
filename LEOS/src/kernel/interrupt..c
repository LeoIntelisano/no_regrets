#include <kernel/interrupt.h>
#include <stdio.h>

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

void load_idt()  {
    idt_descr.base_addr = (uint32_t)idt;
    idt_descr.size = sizeof(idt) - 1;
    __asm__ volatile ("lidt (%0)" :: "r"(&idt_descr));
}