/* 
 * File:   main.c
 * Author: piter cf16 eu
 *
 * Created on May 28, 2014, 7:14 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int *glob_var;
/*
 * 
 */
int main(int argc, char** argv) {

    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *glob_var = 0;
    
    /* fork is called 15 times
     * will create 16 processes
     * 
     * parent, 18099 forks 4 times,
     * it's 1st child 18101 forks 3 times
     * it's 2nd child 18102 forks 2 times (1st child of 18102, the 18110 forks 1 time)
     * it's 3rd child 18104 forks 1 time
     * 1st child of 18101, the 18103 forks 2 times
     * 2nd child of 18101, the 18105 forks 1 time
     * 1st child of 18103, the 18112 forks 1 time
     * detailed description: below main
     */                                 // P - parent after fork
    int pid;                            // c - child after fork                                  18099
    int i = 0;                          //                                                 P,18099 c18101
    for( i = 0; i < 4; ++i)             //                             P,18099 c18102                             P18101 c18103
        pid = fork();                   //               P,18099 c18104        P18102 c18110          P18101 c18105      P18103 c18112
                                        // P,main,18099 c18106  P c,18107  P c18111  P c18115     P c18118  P c18109   P c18113  P c18114   
    sleep(1);
    printf("fork, pid:%d\n", pid);
    (*glob_var)++;
    fflush( stdout);
    
    sleep(1);
    /* I am child, print */
    if( pid==0) printf( "glob_var:%d\n", *glob_var);
    fflush( stdout);
    sleep(10);
    
    munmap(glob_var, sizeof *glob_var);
    
    return (EXIT_SUCCESS);
}
/*
piter@ubuntuamd:/home/piter/include/unix_networking/unpv13e/sctp# ps -ef | grep fork_0
piter     18097  5557  0 19:47 pts/1    00:00:00 /usr/local/netbeans-7.2.1/ide/bin/nativeexecution/Linux-x86_64/pty /bin/sh -c exec "/piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0"
piter     18099 18097  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18101 18099  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18102 18099  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18103 18101  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18104 18099  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18105 18101  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18106 18099  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18107 18104  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18108 18101  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18109 18105  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18110 18102  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18111 18102  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18112 18103  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18113 18103  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18114 18112  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18115 18110  0 19:47 pts/11   00:00:00 /piter/NetBeansProjects/examples/threads/fork_0/dist/Debug/GNU-Linux-x86/fork_0
piter     18121 18010  0 19:47 pts/2    00:00:00 grep --color=auto fork_0
*/

/*
 *output from other run
 *  
fork, pid:18801
fork, pid:18797
fork, pid:18800
fork, pid:18799
fork, pid:18805
fork, pid:18804
fork, pid:0
fork, pid:0
fork, pid:18803
fork, pid:0
fork, pid:18806
fork, pid:0
fork, pid:0
fork, pid:0
fork, pid:0
fork, pid:0
glob_var:16
glob_var:16
glob_var:16
glob_var:16
glob_var:16
glob_var:16
glob_var:16
glob_var:16

RUN SUCCESSFUL (total time: 12s)

 */