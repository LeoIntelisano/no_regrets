; entry.asm
[bits 32]
[extern _start]

call _start ; calls _start() c entrypoint
jmp $
