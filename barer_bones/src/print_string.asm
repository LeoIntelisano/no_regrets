; function to print to console. uses bx as a pointer to the string
print_string:
	pusha
	mov ah, 0x0e

	mov si, 0
print_loop:
	cmp byte [bx + si], 0
	je print_end
	mov al, [bx + si]
	int 0x10
	inc si
	jmp print_loop

print_end:
	popa
	ret

