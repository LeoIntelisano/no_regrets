; asm entry point for kernel for c bootstrapping
; assumes already in protected mode
[bits 32]
[extern _cstart]
[extern pg_handler]
[extern _init]
[extern _fini]

PT_FLAGS equ 0x3; page table flags [Super(0) | R/W | PRES]
PG_FLAGS equ 0x3 ; page flags
PD_ADDR equ 0x1000; page directory addy (from 0x1000 - 0x4000)
PHYS_ADDR equ 0x100000; page first phys address (where our kernel is loaded at 1MB)
IDT_HANDLERS_BASE

section .bss ; pretty sure nasm auto aligns 4-bytes (https://www.nasm.us/xdoc/2.11.08/html/nasmdoc7.html#section-7.9.2)
alignb 16 ; 16 byte align (pad with 0s not nops) for systemV abi (stack should be alligned)
; Initial stack size for boot.asm. C env will handle it's own stack (c calling conventions)
stack_bottom:
resb 16384 ; 16 kb used from bare bones 
stack_top:

section .text.entry

global start
global _#pg

start:
	mov ebp, stack_top ; stack grows down
	mov esp, ebp

	
.paging:	; TODO set up paging
	mov eax, PD_ADDR
	mov ebx, PHYS_ADDR
	mov ecx, 1 ; loop index after first page table
.ident_pde:
	; set first pde for identity mapping
	; *pd_addr = (pd_addr + 4096) | PT_FLAGS
	mov edx, eax
	add edx, 0x1000 ; identity page table starts 1 page afer page directory
	or edx, PT_FLAGS
	mov [eax], edx
.z_pde_loop:
	; for (i = 1; i < 512; i++):
  	;	*(pd_addr + 4*i) = 2
	mov edx, ecx
	shl edx, 2
	mov dword [eax + edx], 2
	inc ecx
	cmp ecx, 512
	jne .z_pde_loop
.kern_pde:
	; Map kernel space (higher-half kernel)
	; *(pd_addr + 4*512) = (pd_addr + 2*4096) | PT_FLAGS
	mov edx, ecx
	shl edx, 2
	mov ebx, PD_ADDR
	add ebx, 0x2000
	or ebx, PT_FLAGS
	mov [eax + edx], ebx
	inc ecx
.z_pde_loop2:
	; Zero out rest of the Page Directory
	; for (i = 513; i < 1024; i++):
  	;	*(pd_addr + 4*i) = 2
	mov edx, ecx
	shl edx, 2
	mov dword [eax + edx], 2 ; w/r on. just not present
	inc ecx
	cmp ecx, 1024
	jne .z_pde_loop2
.ident_pte:
	; // Identity map first 1MB (256 entries) and zero rest
	; for (i = 0; i < 256; i++):
  	;	*(pd_addr + 4096 + 4*i) = (i << 12) | PG_FLAGS
	; for (; i < 1024; i++):
  	;	*(pd_addr + 4096 + 4*i) = 2
	xor ecx, ecx
	mov eax, PD_ADDR
	add eax, 0x1000
.ident_map_loop:
	mov edx, ecx
	shl edx, 2
	cmp ecx, 257	; map one extra page 0x101000 so asm stub isn't a page fault
	jl .first_256
	mov ebx, 2
	jmp .id_pte_asgn
.first_256:
	mov ebx, ecx
	shl ebx, 12
	or ebx, PG_FLAGS
.id_pte_asgn:
	mov [eax + edx], ebx
	inc ecx
	cmp ecx, 1024
	jne .ident_map_loop
.kern_pte:
	; // Fill kernel Page Table
	; for (j = 0; j < 1024; j++):
  	; 	*(pd_addr + 2*4096 + 4*j) = (phys_addr + (j << 12)) | PG_FLAGS
	mov eax, PD_ADDR
	add eax, 0x2000
	xor ecx, ecx
.kern_map_loop:
	mov edx, ecx
	shl edx, 2
	mov ebx, ecx
	shl ebx, 12
	add ebx, PHYS_ADDR
	or ebx, PG_FLAGS
	mov [eax + edx], ebx
	inc ecx
	cmp ecx, 1024
	jne .kern_map_loop

.en_pg:
	mov eax, PD_ADDR
	mov ebx, 0xBEEF
	mov cr3, eax
	mov edx, 0xDEAD
 	mov eax, cr0
 	or eax, 0x80000001
 	mov cr0, eax
	mov eax, 0xC0DE

; TODO set up IDT
	lidt [idt_descriptor]

.pf_hdlr:
.crt:
	call _init
	call _cstart
	call _fini ; kind of unnecessary tbh
	jmp $

_#pg:
	pushad
	mov eax, [esp + 32]	; regs are 4 bytes, PUSHAD: Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI
	push eax
	call pg_handler
	add esp, 4				; pop error code
	popad
	iret

section .bss
idt_descriptor:
	dw idt_end - idt_start - 1  ; limit
	dd idt_start				; base address
	alignb 4
idt_start:
    times(28) dd 0 ; 8 bytes per entry, pad with zeros to get to 14th idx for #pf
.idt_pf:
    dw _#pg & 0xFFFF ; OFFSET 0-15
    dw 8h ; segment selector (0 is null, 8 is code, 16 is data)
    db 0
    db EFh ; P[7], DPL 3 for CPL of usermode [6:5], 0D111 [4:0] D=1 for 32-bit
    dw (_#pg >> 16) & 0xFFFF ; OFFSET 16-31
.idt_fill:    
    times(2*(256 - 15)) dd 0 ; 256 entries, 15 entries in, 8 bytes per entry
idt_end:

