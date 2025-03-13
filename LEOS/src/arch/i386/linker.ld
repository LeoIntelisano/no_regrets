ENTRY(start)

SECTIONS
{
    . = 0x100000;  /* Start at 1MB High Memory */
    _kernel_start = .;

    .text.start ALIGN(4K) : {
        *(.text.entry)
    }
    
    . = 0x80000000 + SIZEOF(.text.start); /* VMA addy after paging is enabled */

    .text ALIGN (4K) : AT(ALIGN(LOADADDR(.text.start) + SIZEOF(.text.start), 4K)) {
        *(.text)              /* Other code */
        *(.init)
        *(.fini)
    }

    .data ALIGN (4K) : AT(ALIGN(LOADADDR(.text) + SIZEOF(.text), 4K)){
        *(.data)              /* Initialized data */
    }
    .rodata ALIGN (4K) : AT(ALIGN(LOADADDR(.data) + SIZEOF(.data), 4K)) {
        *(.rodata)
    }
    .bss ALIGN(4K) : AT(ALIGN(LOADADDR(.rodata) + SIZEOF(.rodata), 4K)) {
        *(.bss)               /* Uninitialized data */
    }
    _kernel_end = .;
    /DISCARD/ : { *(.comment)}
}
