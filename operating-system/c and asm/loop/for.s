/* Programa que realiza um loop de 0 a 9 e imprime a cada interação */

.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	pushl	%ebp
	movl	%esp, %ebp

	push 	$0
	jmp	.L2
.L3:
	mov 	%eax, %ebx
	push 	%eax
	push 	$.LC0
	call	printf
	add 	$1, %ebx
	push 	%ebx
.L2:
	pop 	%eax
	cmp 	$9, %eax
	jle	.L3

	leave
	ret
