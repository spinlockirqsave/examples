	.file	"main.cpp"
	.text
.globl _Z4add1i
	.type	_Z4add1i, @function
_Z4add1i:
.LFB4:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	addl	$1, -4(%rbp)
	leave
	ret
	.cfi_endproc
.LFE4:
	.size	_Z4add1i, .-_Z4add1i
.globl _Z4add2Ri
	.type	_Z4add2Ri, @function
_Z4add2Ri:
.LFB5:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	_Z4add2Ri, .-_Z4add2Ri
	.section	.text._Z4add3i,"axG",@progbits,_Z4add3i,comdat
	.weak	_Z4add3i
	.type	_Z4add3i, @function
_Z4add3i:
.LFB6:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	addl	$1, -4(%rbp)
	leave
	ret
	.cfi_endproc
.LFE6:
	.size	_Z4add3i, .-_Z4add3i
	.section	.text._Z4add4Ri,"axG",@progbits,_Z4add4Ri,comdat
	.weak	_Z4add4Ri
	.type	_Z4add4Ri, @function
_Z4add4Ri:
.LFB7:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	leave
	ret
	.cfi_endproc
.LFE7:
	.size	_Z4add4Ri, .-_Z4add4Ri
	.text
.globl main
	.type	main, @function
main:
.LFB8:
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
	movl	$31, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	_Z4add1i
	leaq	-4(%rbp), %rax
	movq	%rax, %rdi
	call	_Z4add2Ri
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	_Z4add3i
	leaq	-4(%rbp), %rax
	movq	%rax, %rdi
	call	_Z4add4Ri
	movl	$0, %eax
	leave
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
	.section	.note.GNU-stack,"",@progbits
