; Bootloader stub for i386
[bits 16]
[org 0x7c00]

start:
	mov [DISK_NUM], dl
	xor ax, ax
	mov ds, ax
	mov es, ax

	mov bp, 0x9000 ; set the stack to usable memory 0x7E00 to 0x7FFFF
	mov sp, bp
	mov bx, KERNEL_LOADING
	call print_rm
	
	mov bx, PRINT_CHECK
	call print_rm

	mov bx, 0x8000	; load kernel to 0x8000, dl should still have drive number
	mov dh, 1
	mov dl, [DISK_NUM]
	call disk_read_rm
	mov bx, 0x8000
	call print_rm

	mov bx, DISK_READ_SUCCESS
	call print_rm

hang:
	jmp hang
; includes
%include "print_rm.asm"
%include "disk_read_rm.asm"

; globals
KERNEL_LOADING db "loading kernel...",0
PRINT_CHECK db "check 1, 2",0
DISK_READ_SUCCESS db "successful disk read", 0
DISK_NUM db 0

times(510 - ($-$$)) db 0

dw 0xAA55


