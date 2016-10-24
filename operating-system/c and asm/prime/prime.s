	.globl	prime
prime:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	movl 	8(%ebp), %edx		# move o parametro para %edx
	cmpl 	$1, %edx			# compara %edx com 1
	jg	.L2						# goto L2 se for maior

	mov		$0, %eax			# armazena 0 em %eax para retornar, ou seja, retorna falso
	jmp	.exit

.L2:
	movl	$2, 20(%esp)		# move 2 para 20(%esp)
	jmp	.L4						# goto L4

.L6:
	mov		8(%ebp), %eax		# move 8(%ebp) para %eax
	cltd						# long to double long (não entendi isso --')
	idivl	20(%esp)			# divide 20(%esp) por %eax e coloca o resultado é armazenado em %eax e o resto em %edx
	mov		%edx, %eax			# move %edx para %eax (o resto da divisão)
	testl	%eax, %eax			# verifica se %eax == 0, caso verdadeiro o flag ZF será 1 ou em caso contrário será 0
	jne	.L5						# got L5 se ZF != 0
	mov		$0, %eax			# armazena 0 em %eax para retornar, ou seja, retorna falso
	jmp	.exit

.L5:
	add		$1, 20(%esp)		# adiciona 1 em 20(%esp)

.L4:
	mov		20(%esp), %eax		# move 20(%esp) para %eax
	imull	20(%esp), %eax		# multiplica 20(%esp) com %eax e armazena em %eax
	cmp		8(%ebp), %eax		# compara 8(%ebp) com %eax
	jle	.L6						# goto L6 se for menor ou igual
	mov		$1, %eax			# armazena 1 em %eax para retornar, ou seja, retorna verdadeiro

.exit:
	leave
	ret

.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushl	%ebp
	movl	%esp, %ebp

	push	$13
	call	prime

	push	%eax
	push	$.LC0
	call	printf

	leave
	ret
