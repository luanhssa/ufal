; bootloader.asm
; author: Luan

jmp start

%include "src/clear.asm"
%include "src/print.asm"
%include "src/cursor.asm"

msg1 db 'My Bootloader', 0
msg2 db 'Loading Kernel...', 0

start:
	; segment offset
	mov ax, 0x07c0
	mov ds, ax

	xchg bx, bx

	; clear the screen
	call cls

	xchg bx, bx

	; set cursor position to R1, C1
	push $1
	push $1
	call set_cursor_pos

	xchg bx, bx

	; print "my bootloader"
	push msg1
	call print

	xchg bx, bx

	; set cursor position to R2, C1
	push $2
	push $1
	call set_cursor_pos

	xchg bx, bx

	; print "loading kernel..."
	push msg2
	call print

	xchg bx, bx

	; clear the screen
	call cls

	xchg bx, bx

	; load kernel
	call load_kernel

	xchg bx, bx

	; jump to kernel
	jmp 0:0x7e00

load_kernel:

	push bp
	mov bp, sp

	mov ah, 0x02 ; ler do disco
	mov al, 0x02 ; ler 2 setores
	mov ch, 0x00 ; floppy só tem um cilindro.
	mov cl, 0x02 ; segundo setor
	mov dh, 0x00 ; face de cima
	mov dl, 0x00 ; primeiro floppy

	mov bx, 0x800
	mov es, bx ; ES:BX - 512 bytes após o bootloader
	mov bx, 0x00  ;

	int 13h

	leave
	ret

; filling all 512 bytes and the boot signature (0xAA55)
times 510-($-$$) db 0
db 0x55
db 0xAA
