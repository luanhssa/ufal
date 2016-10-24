	.file	"scanf.c"
	.section	.rodata
.in:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	push	%esp #location of input
	push	$.in
	call	scanf

	leave
	ret
