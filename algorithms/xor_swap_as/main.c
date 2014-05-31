/* 
 * File:   main.c
 * Author: piter cf16 eu
 *
 * Created on May 31, 2014, 6:54 PM
 */

#include <stdio.h>
#include <stdlib.h>


void xor_swap_as( int* a, int* b) {
    __asm__(
        //"pushq   %rbp;"             note: omitting pushing a frame second time!
        //"movq   %rsp, %rbp;"              and grabbing arguments!
        //"movq    %rdi, -8(%rbp);"
        //"movq    %rsi, -16(%rbp);"
        "movq    -8(%rbp), %rax;"
        "movl    (%rax), %edx;"         // dereference a
        "movq    -16(%rbp), %rax;"
        "movl    (%rax), %eax;"         // dereference b
        "xorl    %eax, %edx;"           // xor
        "movq    -8(%rbp), %rax;"
        "movl    %edx, (%rax);"         // put result into a
            
        "movq    -16(%rbp), %rax;"
        "movl    (%rax), %edx;"
        "movq    -8(%rbp), %rax;"
        "movl    (%rax), %eax;"
        "xorl    %eax, %edx;"
        "movq    -16(%rbp), %rax;"
        "movl    %edx, (%rax);"
            
        "movq    -8(%rbp), %rax;"
        "movl    (%rax), %edx;"
        "movq    -16(%rbp), %rax;"
        "movl    (%rax), %eax;"
        "xorl    %eax, %edx;"
        "movq    -8(%rbp), %rax;"
        "movl    %edx, (%rax);"     
                                   // note: omitting leaveq retq 2nd time!
    );
}
/*
 * 
 */
int main(int argc, char** argv) {
    int a = 1, b = 2;
    xor_swap_as( &a, &b);
    printf( "%d%d", a, b); // prints 21
    return (EXIT_SUCCESS);
}
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
