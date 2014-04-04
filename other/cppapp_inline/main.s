	.file	"main.cpp"
	.section	.text._ZN3Foo4add1Eii,"axG",@progbits,_ZN3Foo4add1Eii,comdat
	.align 2
	.weak	_ZN3Foo4add1Eii
	.type	_ZN3Foo4add1Eii, @function
_ZN3Foo4add1Eii:
.LFB4:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	addl	$1, -12(%rbp)
	leave
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN3Foo4add1Eii, .-_ZN3Foo4add1Eii
	.section	.text._ZN3Foo4add2ERi,"axG",@progbits,_ZN3Foo4add2ERi,comdat
	.align 2
	.weak	_ZN3Foo4add2ERi
	.type	_ZN3Foo4add2ERi, @function
_ZN3Foo4add2ERi:
.LFB5:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	_ZN3Foo4add2ERi, .-_ZN3Foo4add2ERi
	.text
.globl _Z4add1ii
	.type	_Z4add1ii, @function
_Z4add1ii:
.LFB6:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	addl	$1, -4(%rbp)
	leave
	ret
	.cfi_endproc
.LFE6:
	.size	_Z4add1ii, .-_Z4add1ii
.globl _Z4add2Ri
	.type	_Z4add2Ri, @function
_Z4add2Ri:
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
	.size	_Z4add2Ri, .-_Z4add2Ri
.globl main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$31, -8(%rbp)
	movl	$28, %esi
	movl	$29, %edi
	call	_Z4add1ii
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_Z4add2Ri
	movl	$30, -12(%rbp)
	leaq	-1(%rbp), %rax
	movl	$28, %edx
	movl	$29, %esi
	movq	%rax, %rdi
	call	_ZN3Foo4add1Eii
	leaq	-12(%rbp), %rdx
	leaq	-1(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN3Foo4add2ERi
	movl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	addl	$1, -16(%rbp)
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	movl	$0, %eax
	leave
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
	.section	.note.GNU-stack,"",@progbits
