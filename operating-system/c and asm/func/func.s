	.file	"func.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	f
	.type	f, @function
f:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	push	%eax
	push	$.LC0
	call	printf

	push	$100
	pop	%eax

	leave
	ret
.LFE0:
	.size	f, .-f
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushl	%ebp
	movl	%esp, %ebp

	push	$10
	pop		%eax
	call	f

	push	%eax
	push	$.LC0
	call	printf

	leave
	ret
