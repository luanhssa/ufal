
	.globl	fat
	.type	fat, @function
fat:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp

	mov 	8(%ebp), %eax		# move o parametro para %eax
	push 	%eax				# empilha %eax
	mov 	$1, %edx			# inicia %edx com 1

	jmp	.L2
.L3:
	mov		%edx, %ebx			# guarda o valor de %edx em %ebx
	imull	%eax, %edx			# multiplica %eax por %edx e armazena em %edx
	sub		$1, %eax			# subtrai 1 de %eax
	push 	%eax				# empilha %eax
.L2:
	pop 	%eax				# desempilha no %eax
	cmpl	$1, %eax			# compara 1 com %eax
	jg	.L3						# goto L3 se for maior

	mov 	%edx, %eax			# move %edx para %eax, retornando o resultado.

	leave
	ret
