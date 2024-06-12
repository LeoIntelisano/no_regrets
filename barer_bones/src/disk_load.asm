; disk_load.asm

; load DH sectors to EH:BX from drive DL
disk_load:
	push dx
	
	mov ah, 0x02 ; BIOS READ sector function
	mov al, dh ; read DH sectors
	mov ch, 0x0 ; cylinder 0
	mov dh, 0x0 ; head 0
	mov cl, 0x02 ; start from second sector (after boot sec)
	
	int 0x13 ; BIOS interrupt

	jc disk_error ; jump if carry set

	pop dx
	cmp dh, al ; al sectors read vs dh sectors expected
	jne disk_error
	ret


disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

DISK_ERROR_MSG db "Disk read error!", 0
