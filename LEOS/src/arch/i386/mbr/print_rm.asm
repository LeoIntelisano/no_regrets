; function that prints a string from the address in bx at the segment in ds
print_rm:
	pusha
	mov ah, 0x0e
	xor si, si	

print_loop:
	mov al, [bx+si]
	cmp al, 0
	je done
	int 0x10
	inc si
	jmp print_loop
done:
	popa
	ret

