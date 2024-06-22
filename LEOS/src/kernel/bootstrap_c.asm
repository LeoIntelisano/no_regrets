; asm entry point for kernel for c bootstrapping
; assumes already in protected mode
[bits 32]
[extern _cstart]

global start
start:
				call _cstart
				jmp $
