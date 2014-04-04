#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>


int main (int argc, char **argv)

{

    int i, pid;
    pid = fork();

    printf("Forking...the pid: %d\n", pid);

    for (i = 0; i < 5; i++)
        printf(" %d    %d\n", i, getpid());

    if (pid)
       wait(NULL);

   return 0;

}

