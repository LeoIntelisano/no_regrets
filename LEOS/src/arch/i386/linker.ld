ENTRY(start)

SECTIONS
{
    . = 0x100000;  /* Start at 1MB High Memory */

    .text :
    {
        *(.text.entry)       /* Entry point code */
        *(.text)              /* Other code */
    }

    .data :
    {
        *(.data)              /* Initialized data */
    }

    .bss : ALIGN(4K)
    {
        *(.bss)               /* Uninitialized data */
    }

    /DISCARD/ : { *(.comment) *(.eh_frame) }
}
