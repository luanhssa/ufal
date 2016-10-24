.out:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$48, %esp					# aloca espaço na memória para 12 inteiros (48/4)
	movl	$123, 28(%esp)				# move o inteiro 123 para 28(%esp) - array[0]
	movl	$77, 32(%esp)				# move o inteiro 77 para 32(%esp) - array[1]
	movl	$24, 36(%esp)				# move o inteiro 24 para 36(%esp) - array[2]
	movl	$14, 40(%esp)				# move o inteiro 14 para 40(%esp) - array[3]
	movl	$48, 44(%esp)				# move o inteiro 48 para 44(%esp) - array[4]
	movl	$0, 24(%esp)				# move 0 para 24(%esp) - variável resultado
	movl	$0, 20(%esp)				# move 0 para 20(%esp) para a iteração do for
	jmp	.L2
.L3:
	movl	20(%esp), %eax				# move 0 para o %eax para navegar entre o array
	movl	28(%esp,%eax,4), %eax		# a posição inicial do array está em 28(%esp), 
										# assim a posição 28(%esp + (%eax * 4)) será movida para o %eax
	addl	%eax, 24(%esp)				# soma o %eax com o 
	addl	$1, 20(%esp)				# adiciona 1 ao inteiro que está armazenado em 20(%esp)
.L2:
	cmpl	$4, 20(%esp)				# compara o inteiro 4 com o número armazenado em 20(%esp)
	jle	.L3								# goto L3 caso seja o número seja menor ou igual a 4

	movl	24(%esp), %eax				# move o resultado da soma do array para %eax
	push	%eax						# empilha %eax para imprimir seu valor pelo printf
	push	$.out						# empilha .out (para chamar o printf)
	call	printf

	leave
	ret
