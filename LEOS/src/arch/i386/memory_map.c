#include <stddef.h>
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