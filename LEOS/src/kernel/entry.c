#include <stdint.h>
#include <stdio.h>

#include <kernel/memory_map.h>
#include <kernel/tty.h>
#include <kernel/term.h>
#include <kernel/logging.h>

#include <io/io.h>
#include <drivers/vga.h>

K_TERMINAL* term;


void _cstart() {
	term = &tty_term;
	term->init();
	term->set_color(LIGHT_GRAY, BLACK);
	const char* l = "LEOS";
	k_info(term, "Welcome TO %s\n", l);
//	k_panic(term, "I am panicking\n");
//	k_warn(term, "You should really stop panicking\n");

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