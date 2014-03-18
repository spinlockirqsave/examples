	.file	"main.cpp"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.section	.text._ZN1A1fEv,"axG",@progbits,_ZN1A1fEv,comdat
	.align 2
	.weak	_ZN1A1fEv
	.type	_ZN1A1fEv, @function
_ZN1A1fEv:
.LFB0:
	.file 1 "main.cpp"
	.loc 1 10 0
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
.LCFI0:
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
.LCFI1:
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	.loc 1 10 0
	movl	$15, %eax
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN1A1fEv, .-_ZN1A1fEv
	.section	.text._ZN1B1fEv,"axG",@progbits,_ZN1B1fEv,comdat
	.align 2
	.weak	_ZN1B1fEv
	.type	_ZN1B1fEv, @function
_ZN1B1fEv:
.LFB1:
	.loc 1 15 0
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
.LCFI2:
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
.LCFI3:
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	.loc 1 15 0
	movl	$17, %eax
	leave
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN1B1fEv, .-_ZN1B1fEv
	.section	.text._ZN1AC2Ev,"axG",@progbits,_ZN1AC2Ev,comdat
	.align 2
	.weak	_ZN1AC2Ev
	.type	_ZN1AC2Ev, @function
_ZN1AC2Ev:
.LFB5:
	.loc 1 8 0
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
.LCFI4:
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
.LCFI5:
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
.LBB2:
	.loc 1 8 0
	movq	-8(%rbp), %rax
	movq	$_ZTV1A+16, (%rax)
.LBE2:
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	_ZN1AC2Ev, .-_ZN1AC2Ev
	.section	.text._ZN1BC1Ev,"axG",@progbits,_ZN1BC1Ev,comdat
	.align 2
	.weak	_ZN1BC1Ev
	.type	_ZN1BC1Ev, @function
_ZN1BC1Ev:
.LFB8:
	.loc 1 13 0
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
.LCFI6:
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
.LCFI7:
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
.LBB3:
	.loc 1 13 0
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AC2Ev
	movq	-8(%rbp), %rax
	movq	$_ZTV1B+16, (%rax)
.LBE3:
	leave
	ret
	.cfi_endproc
.LFE8:
	.size	_ZN1BC1Ev, .-_ZN1BC1Ev
	.text
.globl main
	.type	main, @function
main:
.LFB2:
	.loc 1 18 0
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
.LCFI8:
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
.LCFI9:
	.cfi_def_cfa_register 6
	subq	$16, %rsp
.LBB4:
	.loc 1 19 0
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1BC1Ev
	.loc 1 20 0
	movl	$0, %eax
.LBE4:
	.loc 1 21 0
	leave
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.weak	_ZTV1B
	.section	.rodata._ZTV1B,"aG",@progbits,_ZTV1B,comdat
	.align 16
	.type	_ZTV1B, @object
	.size	_ZTV1B, 24
_ZTV1B:
	.quad	0
	.quad	_ZTI1B
	.quad	_ZN1B1fEv
	.weak	_ZTV1A
	.section	.rodata._ZTV1A,"aG",@progbits,_ZTV1A,comdat
	.align 16
	.type	_ZTV1A, @object
	.size	_ZTV1A, 24
_ZTV1A:
	.quad	0
	.quad	_ZTI1A
	.quad	_ZN1A1fEv
	.weak	_ZTS1B
	.section	.rodata._ZTS1B,"aG",@progbits,_ZTS1B,comdat
	.type	_ZTS1B, @object
	.size	_ZTS1B, 3
_ZTS1B:
	.string	"1B"
	.weak	_ZTI1B
	.section	.rodata._ZTI1B,"aG",@progbits,_ZTI1B,comdat
	.align 16
	.type	_ZTI1B, @object
	.size	_ZTI1B, 24
_ZTI1B:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1B
	.quad	_ZTI1A
	.weak	_ZTS1A
	.section	.rodata._ZTS1A,"aG",@progbits,_ZTS1A,comdat
	.type	_ZTS1A, @object
	.size	_ZTS1A, 3
_ZTS1A:
	.string	"1A"
	.weak	_ZTI1A
	.section	.rodata._ZTI1A,"aG",@progbits,_ZTI1A,comdat
	.align 16
	.type	_ZTI1A, @object
	.size	_ZTI1A, 16
_ZTI1A:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1A
	.text
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB0
	.quad	.LCFI0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0
	.quad	.LCFI1
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1
	.quad	.LFE0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST1:
	.quad	.LFB1
	.quad	.LCFI2
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI2
	.quad	.LCFI3
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI3
	.quad	.LFE1
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST2:
	.quad	.LFB5
	.quad	.LCFI4
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI4
	.quad	.LCFI5
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI5
	.quad	.LFE5
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST3:
	.quad	.LFB8
	.quad	.LCFI6
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI6
	.quad	.LCFI7
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI7
	.quad	.LFE8
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST4:
	.quad	.LFB2
	.quad	.LCFI8
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI8
	.quad	.LCFI9
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI9
	.quad	.LFE2
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
	.section	.debug_info
	.long	0x249
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF3
	.byte	0x4
	.long	.LASF4
	.long	.LASF5
	.quad	0x0
	.quad	0x0
	.long	.Ldebug_ranges0+0x0
	.long	.Ldebug_line0
	.uleb128 0x2
	.string	"B"
	.byte	0x8
	.byte	0x1
	.byte	0xd
	.long	0x8e
	.long	0x8e
	.uleb128 0x3
	.long	0x8e
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x1
	.uleb128 0x4
	.byte	0x1
	.string	"B"
	.byte	0x1
	.byte	0x1
	.long	0x5e
	.uleb128 0x5
	.long	0xef
	.byte	0x1
	.uleb128 0x6
	.long	0xf5
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.string	"B"
	.byte	0x1
	.byte	0x1
	.long	0x6f
	.uleb128 0x5
	.long	0xef
	.byte	0x1
	.byte	0x0
	.uleb128 0x7
	.byte	0x1
	.string	"f"
	.byte	0x1
	.byte	0xf
	.long	.LASF0
	.long	0x100
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.long	0x31
	.byte	0x1
	.uleb128 0x5
	.long	0xef
	.byte	0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.string	"A"
	.byte	0x8
	.byte	0x1
	.byte	0x8
	.long	0x8e
	.long	0xef
	.uleb128 0x8
	.long	.LASF6
	.long	0x112
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x1
	.uleb128 0x4
	.byte	0x1
	.string	"A"
	.byte	0x1
	.byte	0x1
	.long	0xbf
	.uleb128 0x5
	.long	0x122
	.byte	0x1
	.uleb128 0x6
	.long	0x128
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.string	"A"
	.byte	0x1
	.byte	0x1
	.long	0xd0
	.uleb128 0x5
	.long	0x122
	.byte	0x1
	.byte	0x0
	.uleb128 0x7
	.byte	0x1
	.string	"f"
	.byte	0x1
	.byte	0xa
	.long	.LASF1
	.long	0x100
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.long	0x8e
	.byte	0x1
	.uleb128 0x5
	.long	0x122
	.byte	0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.byte	0x8
	.long	0x31
	.uleb128 0xa
	.byte	0x8
	.long	0xfb
	.uleb128 0xb
	.long	0x31
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xd
	.long	0x100
	.long	0x112
	.uleb128 0xe
	.byte	0x0
	.uleb128 0x9
	.byte	0x8
	.long	0x118
	.uleb128 0xf
	.byte	0x8
	.long	.LASF7
	.long	0x107
	.uleb128 0x9
	.byte	0x8
	.long	0x8e
	.uleb128 0xa
	.byte	0x8
	.long	0x12e
	.uleb128 0xb
	.long	0x8e
	.uleb128 0x10
	.long	0xd0
	.quad	.LFB0
	.quad	.LFE0
	.long	.LLST0
	.long	0x15e
	.uleb128 0x11
	.long	.LASF2
	.long	0x15e
	.byte	0x1
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0xb
	.long	0x122
	.uleb128 0x10
	.long	0x6f
	.quad	.LFB1
	.quad	.LFE1
	.long	.LLST1
	.long	0x18e
	.uleb128 0x11
	.long	.LASF2
	.long	0x18e
	.byte	0x1
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0xb
	.long	0xef
	.uleb128 0x12
	.long	0xbf
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.long	0x1aa
	.uleb128 0x13
	.long	.LASF2
	.long	0x15e
	.byte	0x1
	.byte	0x0
	.uleb128 0x14
	.long	0x193
	.quad	.LFB5
	.quad	.LFE5
	.long	.LLST2
	.long	0x1d0
	.uleb128 0x15
	.long	0x19f
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0x12
	.long	0x5e
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.long	0x1e7
	.uleb128 0x13
	.long	.LASF2
	.long	0x18e
	.byte	0x1
	.byte	0x0
	.uleb128 0x14
	.long	0x1d0
	.quad	.LFB8
	.quad	.LFE8
	.long	.LLST3
	.long	0x20d
	.uleb128 0x15
	.long	0x1dc
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0x16
	.byte	0x1
	.long	.LASF8
	.byte	0x1
	.byte	0x12
	.long	0x100
	.quad	.LFB2
	.quad	.LFE2
	.long	.LLST4
	.uleb128 0x17
	.quad	.LBB4
	.quad	.LBE4
	.uleb128 0x18
	.string	"b"
	.byte	0x1
	.byte	0x13
	.long	0x31
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x1c
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.uleb128 0x32
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0xa
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.uleb128 0x34
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x10
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x18
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x3b
	.value	0x2
	.long	.Ldebug_info0
	.long	0x24d
	.long	0x133
	.string	"A::f"
	.long	0x163
	.string	"B::f"
	.long	0x1aa
	.string	"A::A"
	.long	0x1e7
	.string	"B::B"
	.long	0x20d
	.string	"main"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x6c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0x0
	.value	0x0
	.value	0x0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.quad	0x0
	.quad	0x0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.Ltext0
	.quad	.Letext0
	.quad	.LFB0
	.quad	.LFE0
	.quad	.LFB1
	.quad	.LFE1
	.quad	.LFB5
	.quad	.LFE5
	.quad	.LFB8
	.quad	.LFE8
	.quad	.LFB2
	.quad	.LFE2
	.quad	0x0
	.quad	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF7:
	.string	"__vtbl_ptr_type"
.LASF3:
	.string	"GNU C++ 4.4.7"
.LASF5:
	.string	"/root/NetBeansProjects/examples/hacker/virtual_table"
.LASF4:
	.string	"main.cpp"
.LASF2:
	.string	"this"
.LASF1:
	.string	"_ZN1A1fEv"
.LASF0:
	.string	"_ZN1B1fEv"
.LASF6:
	.string	"_vptr.A"
.LASF8:
	.string	"main"
	.ident	"GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
	.section	.note.GNU-stack,"",@progbits
