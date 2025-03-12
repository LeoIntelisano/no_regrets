; Bootloader stub for i386
[bits 16]
[org 0x7c00]

KERNEL_SEG equ 0xFFFF
KERNEL_REG equ 0x0010	; Note: If the A20 line is not enabled this will wrap to 0
STACK_SEG equ 0x7000 ; stack is actually at phys addr 0x70000 - 0x100.. Avoid 0x000 sp weirdness
STACK_REG equ 0x100
ENTRY equ 0x100000
MEM_MAP_ADDR equ 0x7E00

start:
	cli
	mov [DISK_NUM], dl
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov ax, STACK_SEG
	mov ss, ax
	mov bp, STACK_REG
	mov sp, bp
	mov si, KERNEL_LOADING
	call print_rm

.map_memory:
	xor ebx, ebx
	mov es, bx
	mov di, MEM_MAP_ADDR

.mem_loop:
	mov eax, 0xE820
	mov ecx, 20
	mov edx, 0x534D4150 ; 'SMAP' magic number
	clc
	int 0x15
	jc .mem_error
	add di, cx
	
	test ebx, ebx
	jnz .mem_loop
	mov word [di], 0xDEAD ; bad practice, but how I will check if memory struct is full

.load_kernel:
	mov bx, KERNEL_SEG
	mov es, bx
	mov bx, KERNEL_REG ; Load Kernel location
	mov dh, 42     ; if you have an issue with the code being funky CHECK THIS!
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

.mem_error:
	mov si, MEM_ERR_MSG
	call print_rm
	jmp $

[bits 32]
protected_mode:
	mov ax, 0x10 ; index 2 (data), TI 0: gdt not ldt, rpl 00 (kernel)
	mov ds, ax
	mov es, ax
	mov ss, ax
	
	; pm mode check
	mov ebx, PM_STRING
	call print_string
	jmp 0x8:0x100000	; Calls asm entry point
	jmp $ 

; includes
%include "print_rm.asm"
%include "disk_read_rm.asm"
%include "gdt.asm"
%include "print_string.asm"

; globals
KERNEL_LOADING db "loading kern",0
DISK_READ_SUCCESS db "disk read", 0
DISK_NUM db 0
MEM_ERR_MSG db "mem err", 0
PM_STRING db "PM", 0

times(510 - ($-$$)) db 0

dw 0xAA55


