#include <stdint.h>
#include <stdio.h>

#include <kernel/memory_map.h>
#include <kernel/tty.h>
#include <kernel/term.h>
#include <kernel/logging.h>
#include <kernel/interrupt.h>

#include <io/io.h>
#include <drivers/vga.h>

extern void _pg();

K_TERMINAL* term;
idt_t idt[MAX_INTERRUPTS];
idt_descr_t idt_descr  __attribute__((aligned(8)));
 
void _cstart() {
	term = &tty_term;
	term->init();
	term->set_color(LIGHT_GRAY, BLACK);
	const char* l = "LEOS";
	k_info(term, "Welcome TO %s\n", l);
//	k_panic(term, "I am panicking\n");
//	k_warn(term, "You should really stop panicking\n");

	k_info(term, "Enabling interrupts...\n");
	set_idt_entry(PF_VEC, &_pg, 0x8, (uint8_t)0xef);
	load_idt();
	k_info(term, "Enabled interrupts\n");
//	__asm__ volatile ("sti");

	__asm__ volatile ("int $14");
//	uint32_t* invalid = 0xdeadbeef;
//	*invalid = 3;

	
	bios_mem_map mem_map[32];
	int ret = get_memory_map(mem_map, sizeof(bios_mem_map)*32);
	if (ret) {
		print_mem_map(term, mem_map, ret);
	}


	
/*
	tty_clear();
//	uint32_t* temp = 0x300000;
//	*temp = "MEMORY VIOLATION";
	
	
	ret ? tty_print("Memory Map copy succeeded!\n") : tty_print("Memory map copy failed\n");
	*/
}
