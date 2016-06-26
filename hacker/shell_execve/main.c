#include <unistd.h>
/*
 * author: Piotr Gregor  peter@
 */
int main() {

    char *shell[2];

    shell[0] = "/bin/sh";
    shell[1] = NULL;
    execve(shell[0], shell, NULL);

    return 0;
}

/*
 \x55\x48\x89\xe5\x48\x83\xec\x10\x48\xc7\x45\xf0\x1c\x06\x40\x00\x48\xc7\x45\xf8\x00\x00\x00\x00\x48\x8b\x45\xf0\x\x48\x8d\x4d\xf0\xba\x00\x00\x00\x00\x48\x89\xce\x48\x89\xc7\xe8\xdc\xfe\xff\xff\xb8\x00\x00\x00\x00\xc9\xc3\x0f\x1f\x44\x00\x00
 */

/*
 * bin/sh
 * 
 main():
0000000000401164 <main> 55                      push   %rbp
0000000000401165 <main+0x1> 48 89 e5                    mov    %rsp,%rbp
0000000000401168 <main+0x4> 48 83 ec 10                 sub    $0x10,%rsp
000000000040116c <main+0x8> 48 c7 45 f0 04 68 49 00     movq   $0x496804,-0x10(%rbp)
0000000000401174 <main+0x10> 48 c7 45 f8 00 00 00 00    movq   $0x0,-0x8(%rbp)
000000000040117c <main+0x18> 48 8b 45 f0                mov    -0x10(%rbp),%rax
0000000000401180 <main+0x1c> 48 8d 4d f0                lea    -0x10(%rbp),%rcx
0000000000401184 <main+0x20> ba 00 00 00 00             mov    $0x0,%edx
0000000000401189 <main+0x25> 48 89 ce                   mov    %rcx,%rsi
000000000040118c <main+0x28> 48 89 c7                   mov    %rax,%rdi
000000000040118f <main+0x2b> e8 5c dc 00 00             callq  000000000040edf0 <__execve>
0000000000401194 <main+0x30> b8 00 00 00 00             mov    $0x0,%eax
0000000000401199 <main+0x35> c9                         leaveq
000000000040119a <main+0x36> c3                         retq
000000000040119b <main+0x37> 0f 1f 44 00 00             nopl   0x0(%rax,%rax,1)
*/