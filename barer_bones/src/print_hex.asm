print_hex:
    ; manipulate chars at HEX_OUT to reflect DX
    pusha
    mov si, 0
    mov ax, dx
    lea bx, HEX_OUT

    ; Write "0x" at the beginning of the buffer
    mov [bx], byte '0'
    mov [bx + 1], byte 'x'

    ; Skip to the end of the buffer
    add bx, 6

hex_loop:
    mov cx, ax          ; Make a copy of ax
    and cx, 0xF         ; Extract the least significant nibble
    cmp cx, 10          ; Compare if it's greater than 9
    jae hex_letter      ; Jump if greater than or equal to 10 (letter)
    add cx, '0'         ; Convert to ASCII character
    jmp hex_write

hex_letter:
    add cx, 'A' - 10    ; Convert to ASCII character

hex_write:
    dec bx              ; Move back one position in the buffer
    mov [bx], cl        ; Store the character in the buffer
    inc si              ; Move to the next nibble
    shr ax, 4           ; Shift ax right by 4 bits to get the next nibble
    cmp si, 4           ; Check if all nibbles are processed
    jne hex_loop        ; If not, continue looping

    ; Print the string
    mov bx, HEX_OUT
    call print_string

    popa
    ret

HEX_OUT: db '0x0000',0
