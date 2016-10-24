global idt_load
idt_load:
	push ebp
	mov ebp, esp
	
	mov eax, [bp+8]
	lidt [eax]

	leave
    ret
