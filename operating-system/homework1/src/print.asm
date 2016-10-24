; print.asm
; author: Luan


print:
	push bp
	mov bp, sp

	mov si, [bp+4]
ch_loop:
	lodsb
	or al, al	; zero=end or str
	jz done		; finish when it is zero
	mov ah, 0x0E
	int 0x10
	jmp ch_loop

done:
	leave
	ret