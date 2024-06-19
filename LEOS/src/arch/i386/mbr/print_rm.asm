; function that prints a string from the address in si at the segment in ds
print_rm:
	pusha
	mov ah, 0x0e

print_loop:
	lodsb
	cmp al, 0
	je done
	int 0x10
	jmp print_loop
done:
	mov al, 0xa ; newline
	int 0x10
	mov al, 0xd ; cr
	int 0x10
	popa
	ret

