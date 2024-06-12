[bits 16]
switch_to_pm:
	cli  ; temporarily disable interrupts
	lgdt [gdt_descriptor] ; load descriptor table

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax ; set first bit of cpu control register

	jmp CODE_SEG:init_pm ; far jump to new segment to 32bit 

[bits 32]
; initialize stack and registers in PM
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000 ; at top of free space
	mov esp, ebp
	call BEGIN_PM
