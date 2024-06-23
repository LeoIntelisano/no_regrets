ENTRY(start)

SECTIONS
{
    . = 0x8000;  /* Start at 0x8000 */

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
