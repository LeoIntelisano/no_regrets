#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

typedef struct bios_mem_map_str{
    uint16_t start_addr_h;
    uint16_t start_addr_l;
    uint16_t end_addr_h;
    uint16_t end_addr_l;
    uint16_t mem_size;
}bios_mem_map;

// returns the total number of entries written, or 0 if it failed or didn't write any bytes
// params: pointer to mem_map array, size in bytes of array
int get_memory_map(bios_mem_map*, int size);

#endif // MEMORY_H