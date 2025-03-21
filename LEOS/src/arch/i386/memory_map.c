#include <stddef.h>
#include <stdio.h>
#include <kernel/memory_map.h>

// TODO find some way to abstract this interface

#define MEM_MAP_ADDR 0x7e00

// TODO swap to kernel memcpy
int get_memory_map(bios_mem_map* mm, int size) {
    int temp = 0;
    uint32_t* addr = (uint32_t*)MEM_MAP_ADDR;
    while (*addr != 0xdead) {
        if (temp + (int)sizeof(bios_mem_map) > size)
            return 0;
        mm->start_addr_l = *addr++;
        mm->start_addr_h = *addr++;
        mm->len_l = *addr++;
        mm->len_h = *addr++;
        mm->mem_type = *addr++;
        mm++;
        temp+= sizeof(bios_mem_map);
    }
    return temp;
}

void print_mem_map(K_TERMINAL* term, bios_mem_map* mem_map, int size) {
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
