ENTRY(start)

SECTIONS
{
    . = 0x100000;  /* Start at 1MB High Memory */
    _kernel_start = .;

    .text.start : {
        *(.text.entry)
    }
    . = 0x80000000; /* VMA addy after paging is enabled */

    .text ALIGN (4K) : AT(ADDR (.text) - 0x80000000) {
        *(.text)              /* Other code */
    }

    .data ALIGN (4K) : AT(ADDR (.data) - 0x80000000){
        *(.data)              /* Initialized data */
    }
    .rodata ALIGN (4K) : AT(ADDR (.rodata) - 0x80000000) {
        *(.rodata)
    }
    .bss ALIGN(4K) : AT(ADDR (.bss) - 0x80000000) {
        *(.bss)               /* Uninitialized data */
    }
    _kernel_end = .;
    /DISCARD/ : { *(.comment) *(.eh_frame) }
}
