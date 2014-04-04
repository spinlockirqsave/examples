	.file	"main.cpp"
	.section	.rodata
.LC0:
	.string	"constant's value: %d\n"
	.text
.globl _Z1fv
	.type	_Z1fv, @function
_Z1fv:
.LFB4:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$99, -4(%rbp)
	leaq	-4(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leave
	ret
	.cfi_endproc
.LFE4:
	.size	_Z1fv, .-_Z1fv
.globl main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$100, -4(%rbp)
	call	_Z1fv
	movl	$0, %eax
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.section	.rodata
	.align 4
	.type	_ZL1a, @object
	.size	_ZL1a, 4
_ZL1a:
	.long	98
	.ident	"GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
	.section	.note.GNU-stack,"",@progbits
