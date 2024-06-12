; boot.asm
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; where to load the kernel in mem

mov [BOOT_DRIVE], dl ; BIOS stores boot drive in DL on POST

mov bp, 0x9000 ; set up stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call load_kernel

call switch_to_pm

jmp $

; include everything so far:
%include "print_string.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string
	mov bx, KERNEL_OFFSET ; parameters for disk_load
	mov dh, 15            ; load first 15 sectors (not boot)
	mov dl, [BOOT_DRIVE]  ; boot disk number
	call disk_load
	ret
[bits 32]
; should be in protected mode now

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET ; jump to kernel code

	jmp $

; Globals
BOOT_DRIVE db 0
MSG_REAL_MODE db "Starting in 16-bit Real Mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory.", 0

; pad bootsector
times 510-($-$$) db 0
dw 0xaa55
