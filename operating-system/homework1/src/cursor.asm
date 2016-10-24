; cursor.asm
; author: Luan

set_cursor_pos:
	push bp
	mov bp, sp

	mov ah, 0x02
	mov bh, 0
	mov dh, [bp+6]
	mov dl, [bp+4]
	int 0x10

	leave
	ret