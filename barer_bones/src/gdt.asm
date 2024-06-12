gdt_start:

gdt_null:
	dd 0x0 ; double word
	dd 0x0
gdt_code: ; code segment descriptor
; base 0x0, limit 0xfffff
; 1st flags: (present)1 (privelege)00 (descr type)1--> 1001b
; type flags: (code)1 (conform)0 (rd)1 (acc)0 -->1010b
; 2nd flags: (granular)1 (32-bit)1 (64 bit)0 (AVL)0--> 1100b
	dw 0xffff ; limit [0-15]
	dw 0x0 ; Base [0-15]
	db 0x0 ; Base [16-23]
	db 10011010b ; 1st flags, type flags
	db 11001111b ; 2nd flags, limit [16-19]
	db 0x0 ; Base [24-31]
	
gdt_data: ; data segment descriptor
; same as above, only difference is type flags:
; type flags:(code)0 (expand)0 (write)1 (acc)0 --> 0010b
	dw 0xffff ; limit [0-15]
	dw 0x0 ; Base [0-15]
	db 0x0 ; Base [16-23]
	db 10010010b ; 1st flags, type flags
	db 11001111b ; 2nd flags, limit [16-19]
	db 0x0 ; Base [24-31]
gdt_end:

gdt_descriptor: ; GDT descriptor
	dw gdt_end - gdt_start 1 
	; Size of gdt, always one less than true size
	dd gdt_start ; start address

; constants for GDT segment descriptor offsets
; When DS = 0x10 in PM, CPU knows we are accessing segment
; at offset 0x10 in GDT. 
; That's data (0x0--> NULL; 0x08 --> CODE; 0x10 --> DATA)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
