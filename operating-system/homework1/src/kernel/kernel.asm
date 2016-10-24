; kernel.asm
; author: Luan

jmp kernel

%include "src/clear.asm"
%include "src/print.asm"
%include "src/cursor.asm"

msg3 db 'My OS', 0

kernel:

	xchg bx, bx

	; set cursor position to R12 C30
	push $12
	push $30
	call set_cursor_pos

	; print "my so"
	push msg3
	call print

	xchg bx, bx

	; loop
	call hang

hang:
	jmp hang