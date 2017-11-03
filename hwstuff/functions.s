main:
        movq    $-4, %rdi
        call    g
        movq    $0, %rax
        ret

.LC0:
	.text
	.globl	main
	.type	main, @function

f:
	cmpq	$-12, %rsi
	jne	.L2
	movq	%rsi, %rax
	movq	%rdi, %rsi
	movq	%rax, %rdi
	call	f
	ret
.L2:
        addq    $1, %rdi
	movq	%rsi, %rax
	imulq	%rdi, %rax
	ret

g:
	leaq	-8(%rdi), %rsi
	leaq	(%rdi,%rdi,2), %rdi
	call	f
	ret
