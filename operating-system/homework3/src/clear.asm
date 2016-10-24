; clear.asm
; author: Luan

global cls

cls:
	push bp
	mov bp, sp

	mov ah, 0x06
	mov al, 0
	mov bh, 0xF
	mov ch, 0
	mov cl, 0
	mov dh, 25
	mov dl, 80
	int 0x10

	leave
	ret