; Bootloader stub for i386
[bits 16]
[org 0x7c00]

KERNEL equ 0x8000

start:
	cli
	mov [DISK_NUM], dl
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov bp, 0x9000 ; set the stack to usable memory 0x7E00 to 0x7FFFF
	mov sp, bp
	mov si, KERNEL_LOADING
	call print_rm

.load_kernel:
	mov bx, KERNEL ; load kernel to 0x8000, dl should still have drive number
	mov dh, 2     ; if you have an issue with the code being funky CHECK THIS!
	mov dl, [DISK_NUM]
	call disk_read_rm
	mov si, DISK_READ_SUCCESS
	call print_rm

.gdt_setup:
	lgdt [gdtr]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp 0x8:protected_mode ; flush pipeline (so all 16 bit instructions are done)

[bits 32]
protected_mode:
	mov ax, 0x10 ; index 2 (data), TI 0: gdt not ldt, rpl 00 (kernel)
	mov ds, ax
	mov es, ax
	mov ss, ax
	
	; pm mode check
	mov ebx, PM_STRING
	call print_string
	call KERNEL
	jmp $ 

; includes
%include "print_rm.asm"
%include "disk_read_rm.asm"
%include "gdt.asm"
%include "print_string.asm"

; globals
KERNEL_LOADING db "loading kernel...",0
DISK_READ_SUCCESS db "successful disk read", 0
DISK_NUM db 0

PM_STRING db "entered protected mode! using VGA interface", 0

times(510 - ($-$$)) db 0

dw 0xAA55


