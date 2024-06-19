; function to read sectors from floppy (CHS) with BIOS
; dh: number of sectors. dl drive number. loads to es:bx
disk_read_rm:
	pusha
	push dx
	
	mov ah, 0x02 ; BIOS READ sector function
	mov al, dh ; read DH sectors
	mov ch, 0x0 ; cylinder 0
	mov dh, 0x0 ; head 0
	mov cl, 0x02 ; start from second sector (after boot sec)int 0x13

	int 0x13

	jc .disk_error
	pop dx
	cmp dh, al
	jne .disk_error
	popa
	ret

.disk_error:
	mov si, DISK_ERROR_MSG
	call print_rm
	jmp $

DISK_ERROR_MSG db "disk read failed... halting execution", 0

