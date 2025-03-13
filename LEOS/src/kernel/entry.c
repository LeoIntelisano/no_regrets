#include <stdint.h>
#include "tty/tty.h"
#include "io/io.h"
#include "drivers/dt.h"
#include "drivers/vga.h"
#include "kernel/memory_map.h"

void _cstart() {
	tty_clear();
	
//	uint32_t* temp = 0x300000;
//	*temp = "MEMORY VIOLATION";
	bios_mem_map mem_map[32];
	int ret = get_memory_map(mem_map, sizeof(bios_mem_map)*32);
	
	ret ? tty_print("Memory Map copy succeeded!\n") : tty_print("Memory map copy failed\n");
	
	
	tty_print("Hello, Kernel World!\n");
	uint8_t test = _test_asm();
	if (test == 1) {
		tty_print("Houston, we got a problem\n");
	} 
	if (test == 4) {
		tty_print("The asm stuff worked!?\n");
	}
	link_test();
	tty_set_attr(0x3);
	tty_print("TTY Attribute Change");
}
 