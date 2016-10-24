global gdt_load

gdt_load:

	push ebp
	mov ebp, esp

	xchg bx, bx

	mov eax, [ebp+8]

	lgdt [eax]

;	mov eax, 0x08

;	jmp 

	leave
	ret