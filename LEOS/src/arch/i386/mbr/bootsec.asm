; Bootloader stub for i386
[bits 16]
[org 0x7c00]

start:
	xor ax, ax
;	mov cs, ax
	mov ds, ax
	mov es, ax
;	mov ss, ax

	mov bp, 0x9000 ; set the stack to usable memory 0x7E00 to 0x7FFFF
	mov sp, bp
	mov bx, KERNEL_LOADING
	call print_rm

; includes
%include "print_rm.asm"

; globals
KERNEL_LOADING db "loading kernel...", 0

times(510 - ($-$$)) db 0

dw 0xAA55


