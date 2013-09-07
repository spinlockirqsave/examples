	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"/bin/sh"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$.LC0, -16(%rbp)
	movq	$0, -8(%rbp)
	movq	-16(%rbp), %rax
	leaq	-16(%rbp), %rcx
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	execve
	movl	$0, %eax
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
	.section	.note.GNU-stack,"",@progbits
