/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 13, 2013, 3:34 PM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int i=44, *p = &i;
    int **p2p = &p;
    printf(" i: %d",*p);//0x7fff4d24ae8c
    return 0;
}

//disassm of printf(" i: %d",i);
//!int main(int argc, char** argv) {
//main(int, char**)+0: push   %rbp
//main(int, char**)+1: mov    %rsp,%rbp
//main(int, char**)+4: sub    $0x30,%rsp
//main(int, char**)+8: mov    %edi,-0x24(%rbp)
//main(int, char**)+11: mov    %rsi,-0x30(%rbp)
//!
//!    int i=44, *p = &i;
//main(int, char**)+15: movl   $0x2c,-0x4(%rbp)
//main(int, char**)+22: lea    -0x4(%rbp),%rax
//main(int, char**)+26: mov    %rax,-0x10(%rbp)
//!    int **p2p = &p;
//main(int, char**)+30: lea    -0x10(%rbp),%rax
//main(int, char**)+34: mov    %rax,-0x18(%rbp)
//!    printf(" i: %d",i);//0x7fff4d24ae8c
//main(int, char**)+38: mov    -0x4(%rbp),%eax
//main(int, char**)+41: mov    %eax,%esi
//main(int, char**)+43: mov    $0x40070c,%edi
//main(int, char**)+48: mov    $0x0,%eax
//main(int, char**)+53: callq  0x4004c0 <printf@plt>
//!    return 0;
//main(int, char**)()
//main(int, char**)+58: mov    $0x0,%eax
//!}
//main(int, char**)+63: leaveq 
//main(int, char**)+64: retq


//printf(" i: %p",p);
//!int main(int argc, char** argv) {
//main(int, char**)+0: push   %rbp
//main(int, char**)+1: mov    %rsp,%rbp
//main(int, char**)+4: sub    $0x30,%rsp
//main(int, char**)+8: mov    %edi,-0x24(%rbp)
//main(int, char**)+11: mov    %rsi,-0x30(%rbp)
//!    int i=44, *p = &i;
//main(int, char**)+15: movl   $0x2c,-0x4(%rbp)
//main(int, char**)+22: lea    -0x4(%rbp),%rax
//main(int, char**)+26: mov    %rax,-0x10(%rbp)
//!    int **p2p = &p;
//main(int, char**)+30: lea    -0x10(%rbp),%rax
//main(int, char**)+34: mov    %rax,-0x18(%rbp)
//!    printf(" i: %p",p);//0x7fff4d24ae8c
//main(int, char**)+38: mov    -0x10(%rbp),%rax
//main(int, char**)+42: mov    %rax,%rsi
//main(int, char**)+45: mov    $0x40070c,%edi
//main(int, char**)+50: mov    $0x0,%eax
//main(int, char**)+55: callq  0x4004c0 <printf@plt>
//!    return 0;
//main(int, char**)()
//main(int, char**)+60: mov    $0x0,%eax
//!}
//main(int, char**)+65: leaveq 
//main(int, char**)+66: retq 