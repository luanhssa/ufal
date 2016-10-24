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
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$.LC0, %eax
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
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
	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 24(%esp)
	movl	$20, 28(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	f
	leave
	ret
