; bootloader.asm
; author: Luan

start:

;	xchg bx, bx
	
	push 0x820
	call load_kernel
	
;	xchg bx, bx

	cli

	call load_gdt

;	xchg bx, bx

	call switch_protected_mode

	xchg bx, bx

	; jump to kernel
	jmp 0x08:0x8200


load_kernel:

	push bp
	mov bp, sp

	mov ah, 0x02 ; ler do disco
	mov al, 0x30 ; ler 30h setores
	mov ch, 0x00 ; floppy só tem um cilindro.
	mov cl, 0x02 ; segundo setor
	mov dh, 0x00 ; face de cima
	mov dl, 0x00 ; primeiro floppy

	mov bx, [bp+4]
	mov es, bx ; ES:BX - 512 bytes após o bootloader
	mov bx, 0x00  ;

	int 13h

	leave
	ret

load_gdt:

	push bp
	mov bp, sp	

	mov ax, 0x7c0
	mov ds, ax

	lgdt [gdt_ptr]

	leave
	ret

gdt_ptr:
	dw	24
	dd	0x7c00 + gdt

gdt:
	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	; null segment
	db 0xff, 0xee, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00	; code segment
	db 0xff, 0xee, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00	; data segment

switch_protected_mode:

	push bp
	mov bp, sp

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax

	leave
	ret

; filling all 512 bytes and the boot signature (0xAA55)
times 510-($-$$) db 0
db 0x55
db 0xAA
