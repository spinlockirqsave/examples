#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

 
//OK. concurrency_1
int main (int argc, char **argv)

{

    int i, pid,pid2;
    if(pid = fork()){// old process pid= getpid() of new process, new process pid=0
                 // new process getpid usually=old process getpid+1
//        so: New process starts execution by returning from fork().
//        Child and parent are nearly identical.
//        Parent gets the child process id from fork().
//        Child gets 0 back from fork().
//        Parent should wait for child to exit.
        if(pid>0){
            printf("Parent...the pid: %d\n", pid);
            printf("Parent...the id: %d\n", getpid());
        }else printf("Error: %d\n", pid);
    }else if(pid==0){
        printf("Child...the pid: %d\n", pid);
        printf("Child...the id: %d\n", getpid());
    }
    
    //pid2=fork();


//    if (pid)
//       wait(NULL);
    for(i=0;i<5;i++)
        printf("If id: %d\n", getpid());
   printf("Returning id: %d\n", getpid());
   return 0;

}

