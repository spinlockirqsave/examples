/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 18, 2013, 10:04 PM
 */

#include <cstdlib>

using namespace std;
#include<stdio.h>
#include<errno.h>
#include <string.h>
int sendmail(const char *to, const char *from, const char *subject, const char *message){
    int retval = -1;
    FILE *mailpipe = popen("sendmail -t", "w");
    if (mailpipe != NULL)
    {
        fprintf(mailpipe, "To: %s\n", to);
        fprintf(mailpipe, "From: %s\n", from);
        fprintf(mailpipe, "Subject: %s\n\n", subject);
        fwrite(message, 1, strlen(message), mailpipe);
        fwrite(".\n", 1, 2, mailpipe);
        pclose(mailpipe);
        retval = 0;
     }
     else{
         perror("Failed to invoke sendmail");
     }
     return retval;
}
/*
 * 
 */
int main(int argc, char** argv) {

    int res=sendmail("rocket@gmail.com","ubuntu","new_subject","how are you Piter?");
    return 0;
}

