/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 15, 2014, 11:48 AM
 */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char * argv[])
{
   int pipefd[ 2];
   pid_t cpid;
   char buf;

   pipe( pipefd); // create the pipe
   cpid = fork(); // duplicate the current process
   if (cpid == 0) // if I am the child then
   {
       close( pipefd[ 0]); // close the read-end of the pipe
       write( pipefd[ 1], "OK", 3); // send name to the server
       write( 1, "\n", 1);
       exit( EXIT_SUCCESS);
   }
   else // if I am the parent then
   {
       close( pipefd[ 1]); // close the write-end of the pipe
       while ( read( pipefd[ 0], &buf, 1) > 0) // read while EOF
           write( 1, &buf, 1);
       close( pipefd[0]); // close the read-end of the pipe;
       close( pipefd[ 1]); // close the write-end of the pipe
       write( 1, "\n", 1);
       wait( NULL); // wait for the child process to exit before I do the same
       exit( EXIT_SUCCESS);
   }
   return 0;
}

