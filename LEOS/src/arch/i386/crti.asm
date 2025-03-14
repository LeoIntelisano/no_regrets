; GNU C Runtime _init and _fini headers
section .init
global _init
_init:
    push ebp
    mov ebp, esp

section .fini
global _fini
_fini:
    push ebp
    mov ebp, esp