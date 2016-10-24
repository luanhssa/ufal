; author: Luan
; gdt.asm


load_gdt:

	push bp
	mov bp, sp

	cli				; no interrupt

	; segment offset
	mov ax, 0x07c0
	mov ds, ax

	lgdt [gdt_ptr]	; load gdt pointer

	sti

	leave
	ret


gdt_ptr:
	dw 24
	dd 0x7c00 + gdt

gdt:
	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	; null segment
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00	; code segment
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00	; data segment
