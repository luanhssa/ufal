	.file	"printf.c"
	.section	.rodata
.LC0:
	.string	"Hello, Wworld! = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 28(%esp)
	movl	28(%esp), %eax

	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf

	leave
	ret
