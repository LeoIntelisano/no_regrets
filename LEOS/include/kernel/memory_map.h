#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H
#include <stdint.h>

typedef enum bios_availability_enum {
    __xxx__, USABLE, RESERVED  
}bios_availability;

typedef struct bios_mem_map_str{
    uint32_t start_addr_l;
    uint32_t start_addr_h;
    uint32_t len_l;
    uint32_t len_h;
    uint32_t mem_type;
}bios_mem_map;

// returns the total number of entries written, or 0 if it failed or didn't write any bytes
// params: pointer to mem_map array, size in bytes of array
int get_memory_map(bios_mem_map*, int size);

#endif // MEMORY_MAP_H