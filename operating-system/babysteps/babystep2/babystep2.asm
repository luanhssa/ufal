
	mov ah, 0x0A
	mov al, 'W'
	mov bh, 0
	mov cx, 10
	int 0x10

hang:
	jmp hang

times 510-($-$$) db 0
db 0x55
db 0xAA