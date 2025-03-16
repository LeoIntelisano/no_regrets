#include <stdint.h>
#include <stdio.h>

#include <kernel/memory_map.h>
#include <kernel/tty.h>
#include <kernel/term.h>
#include <kernel/logging.h>

#include <io/io.h>
#include <drivers/vga.h>

K_TERMINAL* term;

void print_mem_map(bios_mem_map* mem_map, int size) {
	if (size <= 0 || size % sizeof(bios_mem_map) != 0) {
		k_printf(term, "Error: Invalid memory map data\n");
		return;
	}
	k_printf(term, "Memory Map:\n");
		for (int i = 0; i < size /(int)sizeof(bios_mem_map); i++) {
			const char* avail = mem_map[i].mem_type == USABLE ? "F" : "R/U";
			uint64_t start = ((uint64_t)mem_map[i].start_addr_h << 32) | mem_map[i].start_addr_l;
    		uint64_t length = ((uint64_t)mem_map[i].len_h << 32) | mem_map[i].len_l;
    		uint64_t end = start + length;
			
			term->set_color(GREEN, BLACK);
			k_printf(term, "\tStart: ");
			term->set_color(LIGHT_GRAY, BLACK);
			k_printf(term, "0x%x%x\t", mem_map[i].start_addr_h, mem_map[i].start_addr_l);
			
			term->set_color(GREEN, BLACK);
			k_printf(term, "End: ");
			term->set_color(LIGHT_GRAY, BLACK);
			k_printf(term, "0x%x%x\t", (uint32_t)(end >> 32), (uint32_t)end);
			
			term->set_color(GREEN, BLACK);
			k_printf(term, "Avail: ");
			term->set_color(LIGHT_GRAY, BLACK);
			k_printf(term, "%s\t", avail);
			term->set_color(GREEN, BLACK);
			k_printf(term, "Size: ");
			term->set_color(LIGHT_GRAY, BLACK);
			k_printf(term, "0x%x%x\n", mem_map[i].len_h, mem_map[i].len_l);
		}
}

void _cstart() {
	term = &tty_term;
	term->init();
	term->set_color(LIGHT_GRAY, BLACK);
	const char* l = "LEOS";
	k_info(term, "Welcome TO %s\n", l);
//	k_panic(term, "I am panicking\n");
//	k_warn(term, "You should really stop panicking\n");

	
//	k_printf(term, "string test %s", l);
//	k_printf(term, "is this 0x31dead13BEEF? 0x%x%X", (int)0x31dead13, 0xBEEF);
//	k_printf(term, "Some sporadic zeros: %X %x %i", 0, 0x1000, 0);
//	k_printf(term, "is this 10: %d", (int)10);
//	k_printf(term, "is this -10: %d", (int)-10);

	bios_mem_map mem_map[32];
	int ret = get_memory_map(mem_map, sizeof(bios_mem_map)*32);
	if (ret) {
		print_mem_map(mem_map, ret);
	}

/*
	tty_clear();
//	uint32_t* temp = 0x300000;
//	*temp = "MEMORY VIOLATION";
	
	
	ret ? tty_print("Memory Map copy succeeded!\n") : tty_print("Memory map copy failed\n");
	*/
}