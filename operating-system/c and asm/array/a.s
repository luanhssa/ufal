.LC0:
	.string	"%d\n"
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
	mov 	%eax, %ebx			# armazena o valor de %eax em %ebx pois a funcao printf modifica o valor de %eax
	push 	%eax				# empilha %eax para imprimir seu valor pelo printf
	push 	$.LC0				# empilha .LCO (para chamar o printf)
	call	printf
	add 	$1, %ebx			# adiciona 1 ao inteiro que está armazenado em 20(%esp)
	push 	%ebx
.L2:
	pop 	%eax
	cmp 	$9, %eax			# compara o inteiro 9 com o número armazenado em 20(%esp)
	jle	.L3						# goto L3 caso seja o número seja menor ou igual a 9

	leave
	ret
