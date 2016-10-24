global gdt_load
gdt_load:
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]
	lgdt [eax]

	leave
	ret
