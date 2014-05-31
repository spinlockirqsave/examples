/* 
 * File:   main.c
 * Author: piter cf16 eu
 *
 * Created on May 31, 2014, 6:36 PM
 */

#include <stdio.h>
#include <stdlib.h>

void xor_swap( int* a, int* b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
}
/*
 * 
 */
int main(int argc, char** argv) {
    int a = 13;
    return (EXIT_SUCCESS);
}

/*
         .file   "main.c"
        .text
.globl xor_swap
        .type   xor_swap, @function
xor_swap:
.LFB0:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        movq    %rsp, %rbp
        .cfi_offset 6, -16
        .cfi_def_cfa_register 6
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        movq    -8(%rbp), %rax
        movl    (%rax), %edx
        movq    -16(%rbp), %rax
        movl    (%rax), %eax
        xorl    %eax, %edx
        movq    -8(%rbp), %rax
        movl    %edx, (%rax)
        movq    -16(%rbp), %rax
        movl    (%rax), %edx
        movq    -8(%rbp), %rax
        movl    (%rax), %eax
        xorl    %eax, %edx
        movq    -16(%rbp), %rax
        movl    %edx, (%rax)
        movq    -8(%rbp), %rax
        movl    (%rax), %edx
        movq    -16(%rbp), %rax
        movl    (%rax), %eax
        xorl    %eax, %edx
        movq    -8(%rbp), %rax
        movl    %edx, (%rax)
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   xor_swap, .-xor_swap
.globl main
        .type   main, @function
main:
.LFB1:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        movq    %rsp, %rbp
        .cfi_offset 6, -16
        .cfi_def_cfa_register 6
        movl    %edi, -20(%rbp)
        movq    %rsi, -32(%rbp)
        movl    $13, -4(%rbp)
        movl    $0, %eax
        leave
        ret
        .cfi_endproc
.LFE1:
        .size   main, .-main
        .ident  "GCC: (Ubuntu/Linaro 4.4.7-2ubuntu1) 4.4.7"
        .section        .note.GNU-stack,"",@progbits
 */

/*
 00000000004004b4 <xor_swap>:
  4004b4:	55                   	push   %rbp
  4004b5:	48 89 e5             	mov    %rsp,%rbp
  4004b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  4004bc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  4004c0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004c4:	8b 10                	mov    (%rax),%edx
  4004c6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4004ca:	8b 00                	mov    (%rax),%eax
  4004cc:	31 c2                	xor    %eax,%edx
  4004ce:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004d2:	89 10                	mov    %edx,(%rax)
  4004d4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4004d8:	8b 10                	mov    (%rax),%edx
  4004da:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004de:	8b 00                	mov    (%rax),%eax
  4004e0:	31 c2                	xor    %eax,%edx
  4004e2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4004e6:	89 10                	mov    %edx,(%rax)
  4004e8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004ec:	8b 10                	mov    (%rax),%edx
  4004ee:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4004f2:	8b 00                	mov    (%rax),%eax
  4004f4:	31 c2                	xor    %eax,%edx
  4004f6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4004fa:	89 10                	mov    %edx,(%rax)
  4004fc:	c9                   	leaveq 
  4004fd:	c3                   	retq   
*/