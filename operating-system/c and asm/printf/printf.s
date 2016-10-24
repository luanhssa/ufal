	.file	"hw.c"
.out:
	.string	"Hello Assembly World!\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	push	$.out
	call	printf

	leave
	ret
