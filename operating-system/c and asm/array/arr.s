.LC0:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$64, %esp			# aloca espaço na memória para 16 inteiros
	push 	$0					# empilha 0
	jmp	.L2 					# goto L2
.L3:
	pop 	%edx
	mov		%edx, %eax
	sall	$2, %eax
	add		%edx, %eax
	add		%eax, %eax
	add		%eax, %edx
	push 	%edx
	mov 	%edx, %ebx
	add		$1, %ebx
	push 	%ebx
.L2:
	pop 	%eax
	cmp 	$9, %eax			# compara o inteiro 9 com o número armazenado em 20(%esp)
	jle	.L3						# goto L3 caso seja o número seja menor ou igual a 9


	push 	$0					# empilha 0
	jmp	.L4 					# goto L2
.L5:
	movl	20(%esp), %eax
	movl	24(%esp,%eax,4), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	addl	$1, 20(%esp)
.L4:
	pop 	%eax
	cmp 	$9, %eax			# compara o inteiro 9 com o número armazenado em 20(%esp)
	jle	.L5						# goto L3 caso seja o número seja menor ou igual a 9

	leave
	ret
