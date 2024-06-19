; Bootloader stub for i386
[bits 16]
[org 0x7c00]

KERNEL equ 0x8000

start:
	mov [DISK_NUM], dl
	xor ax, ax
	mov ds, ax
	mov es, ax

	mov bp, 0x9000 ; set the stack to usable memory 0x7E00 to 0x7FFFF
	mov sp, bp
	mov si, KERNEL_LOADING
	call print_rm

.load_kernel:
	mov bx, KERNEL ; load kernel to 0x8000, dl should still have drive number
	mov dh, 1
	mov dl, [DISK_NUM]
	call disk_read_rm
	mov si, DISK_READ_SUCCESS
	call print_rm
	
	
	jmp $ 

; includes
%include "print_rm.asm"
%include "disk_read_rm.asm"

; globals
KERNEL_LOADING db "loading kernel...",0
DISK_READ_SUCCESS db "successful disk read", 0
DISK_NUM db 0

times(510 - ($-$$)) db 0

dw 0xAA55


