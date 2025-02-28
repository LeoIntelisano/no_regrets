; asm entry point for kernel for c bootstrapping
; assumes already in protected mode
[bits 32]
[extern _cstart]

section .bss ; pretty sure nasm auto aligns 4-bytes (https://www.nasm.us/xdoc/2.11.08/html/nasmdoc7.html#section-7.9.2)
alignb 16 ; 16 byte align (pad with 0s not nops) for systemV abi (stack should be alligned)
; Initial stack size for boot.asm. C env will handle it's own stack (c calling conventions)
stack_bottom:
resb 16384 ; 16 kb used from bare bones 
stack_top:

section .text.entry

global start
start:
	mov ebp, stack_top ; stack grows down
	mov esp, ebp

	
paging:	; TODO set up paging
	


	; TODO set up IDT
	call _cstart
	jmp $
