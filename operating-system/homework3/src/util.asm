global breakpoint

breakpoint:
	push ebp
	mov ebp, esp	

	xchg bx, bx

	leave
	ret
	