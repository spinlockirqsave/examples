/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 6, 2013, 1:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    puts(hostname);

    return EXIT_SUCCESS;
}

