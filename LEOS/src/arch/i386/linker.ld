ENTRY(start)

SECTIONS
{
    . = 0x8000;  /* Start at 1MB */

    .text : AT(ADDR(.text) - 0x100000)
    {
        *(.text.entry)       /* Entry point code */
        *(.text)              /* Other code */
    }

    .data :
    {
        *(.data)              /* Initialized data */
    }

    .bss :
    {
        *(.bss)               /* Uninitialized data */
    }

    /DISCARD/ : { *(.comment) *(.eh_frame) }
}
