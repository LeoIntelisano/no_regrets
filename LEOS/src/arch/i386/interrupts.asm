[bits 32]
[extern sys_isr_disp]

%macro ISR_NO_ERR 1
global isr_%1
isr_%1:
    push dword 0  ; to align stack with isrs with ec
    push dword %1 ; isr number
    pushad
    call sys_isr_disp
    popad
    add esp, 8
    iret
%endmacro

%macro ISR_ERR 1
global isr_%1
isr_%1:
    push dword %1 ; isr number
    pushad
    call sys_isr_disp
    popad
    add esp, 4
    iret
%endmacro

section .text

ISR_NO_ERR  0  ; DE: Divide Error             F
ISR_NO_ERR  1  ; DB: Debug Exception          F/T
ISR_NO_ERR  2  ; NMI: Non Maskable Interrupt  I
ISR_NO_ERR  3  ; BP: Breakpoint               T
ISR_NO_ERR  4  ; OF: Overflow                 T
ISR_NO_ERR  5  ; BR: BOUND Range Exceeded     F
ISR_NO_ERR  6  ; UD: Invalid Opcode           F
ISR_NO_ERR  7  ; NM: No math co-processor     F
ISR_ERR     8  ; DF: Double Fault             A  err=0
; ISR 9 is reserved
ISR_NO_ERR  9  ; RESERVED
ISR_ERR     10 ; TS: Invalid TSS              F
ISR_ERR     11 ; NP: Segment Not Present      F
ISR_ERR     12 ; SS: Stack-Segment Fault      F
ISR_ERR     13 ; GP: General Protection       F
ISR_ERR     14 ; PF: Page Fault               F special err
; ISR 15 also reserved
ISR_NO_ERR  15 ; RESERVED
ISR_NO_ERR  16 ; MF: MothaFucka JK Math Error F
ISR_ERR     17 ; AC: Aligment Check           F
ISR_NO_ERR  18 ; MC: Machine Check            A
ISR_NO_ERR  19 ; XM: SIMD FP Exception        F
ISR_NO_ERR  20 ; VE: Virtualization Exception F
ISR_ERR     21 ; CP: Control Protection       F
; 22 - 31 res
; 32 - 255 user-def
; TODO Maybe add PIC stuff here soon
ISR_NO_ERR  67 ; system calls                 I

section .rodata
; isr table loop
global isr_table
isr_table:
%assign i 0
%rep 256
%if i > 21 && i != 67
dd 0
%else
dd isr_%+i
%endif
%assign i i+1
%endrep