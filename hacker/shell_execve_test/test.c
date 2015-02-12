/* 
 * File:   test.c
 * Author: Piotr Gregor  peter cf16.eu
 *
 * Created on August 27, 2013, 3:45 AM
 */

#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

char code_v2[] = "\x01\xb8\x00\x00\xbb\x00\x00\x2a\x00\x00\x80\xcd";
char code_v1[] = "\xb8\x01\x00\x00\x00\xbb\x2a\x00\x00\x00\xcd\x80";
char code_v3[] = "\x55\x48\x89\xe5\x89\x7d\xfc\x48\x89\x75\xf0\xb8\x2a\x00\x00\x00\xc9\xc3";

char code[] = {0x55,0x48,0x89,0xe5,0x89,0x7d,0xfc,0x48,0x89,0x75,0xf0,0xb8,0x2a,0x00,0x00,0x00,0xc9,0xc3,0x00};    // return  42 0x2a
char code255[] = {0x55,0x48,0x89,0xe5,0x89,0x7d,0xfc,0x48,0x89,0x75,0xf0,0xb8,0xFF,0x00,0x00,0x00,0xc9,0xc3,0x00}; // return 255 0xFF
char code15[] = {0x55,0x48,0x89,0xe5,0x89,0x7d,0xfc,0x48,0x89,0x75,0xf0,0xb8,0x0F,0x00,0x00,0x00,0xc9,0xc3,0x00};  // return  15 0x0F

char code_binsh[] = {0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x10,0x48,0xc7,0x45,0xf0,0x04,0x68,0x49,0x00,0x48,
0xc7,0x45,0xf8,0x00,0x00,0x00,0x00,0x48,0x8b,0x45,0xf0,0x48,0x8d,0x4d,0xf0,0xba,0x00,0x00,0x00,0x00,0x48,0x89,
0xce,0x48,0x89,0xc7,0xe8,0x5c,0xdc,0x00,0x00,0xb8,0x00,0x00,0x00,0x00,0xc9,0xc3,0x0f,0x1f,0x44,0x00,0x00};

/*
 * return 42
 * 
 00000000004000e0 <.text>:
  4000e0:	b8 01 00 00 00       	mov    $0x1,%eax
  4000e5:	bb 2a 00 00 00       	mov    $0x2a,%ebx
  4000ea:	cd 80                	int    $0x80
 * 
 * 
 * hexdump a.out:
 * 01b8 0000 bb00 002a 0000 80cd
*/

/*
 * 00000000004004b4 <main> 55                   	push   %rbp
00000000004004b5 <main+0x1> 48 89 e5             	mov    %rsp,%rbp
00000000004004b8 <main+0x4> 89 7d fc             	mov    %edi,-0x4(%rbp)
00000000004004bb <main+0x7> 48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/root/NetBeansProjects/examples/hacker/tiny_c/tiny.c:15

    return 42;
00000000004004bf <main+0xb> b8 2a 00 00 00       	mov    $0x2a,%eax
/root/NetBeansProjects/examples/hacker/tiny_c/tiny.c:16
}
00000000004004c4 <main+0x10> c9                   	leaveq 
00000000004004c5 <main+0x11> c3                   	retq 
 */
int main(int argc, char **argv)
{
///*creating a function pointer*/
//int (*func)();
//func = (int (*)()) code_v3;
//(int)(*func)();
    
    void *buf;

  /* copy code to executable buffer */    
  buf = mmap (0,sizeof(code),PROT_READ|PROT_WRITE|PROT_EXEC,
              MAP_PRIVATE|MAP_ANON,-1,0);
  memcpy (buf, code, sizeof(code));

  /* run code */
  int i = ((int (*) (void))buf)();
  printf("got this done. returned: %d\n", i);
return 0;
}

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
