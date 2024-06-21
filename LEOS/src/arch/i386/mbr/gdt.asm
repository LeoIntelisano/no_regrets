; configure a simple gdt to enter protected mode
; code and data have full access to 4GB address space
gdt_start:
	; null descriptor
	dd 0x0
	dd 0x0
.gdt_code:	
	; Code segment descriptor
	dw 0xffff    ; LIMIT (0-15)
	dw 0x0000    ; BASE (0-15)
	db 0x00	     ; BASE (16-23)
	db 10011010b ; ACCESS: present, ring 0, code seg, xr, res
	db 11001111b ; LIMIT (16-19), GRANULARITY: 4kb, 32-bit
	db 0x00      ; BASE (24-31)
.gdt_data:
	; Data segment descriptor
	dw 0xffff
	dw 0x0000
	db 0x00
	db 10010010b ; ACCESS: present, ring 0, data seg, rw, res
	db 11001111b
	db 0x00
gdt_end:

gdtr:
	dw gdt_end - gdt_start -1 ; size
	dd gdt_start ; offset

