/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 21, 2013, 1:17 AM
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 3334

int main() {
    int sockfd; /* socket file descriptor */
    struct sockaddr_in my_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server-socket() error lol!");
        exit(1);
    } else
        printf("Server-socket() sockfd is OK...\n");

    //    Sometimes, you might notice, you try to rerun a server 
    //    and bind() fails, claiming "Address already in use".
    //    This means a socket that was connected is still hanging around in the kernel,
    //    and it’s hogging the port. You can either wait for it to clear (a minute or so),
    //    or add code to your program allowing it to reuse the port, like this:
    int yes = 1;
    /* "Address already in use" error message */
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1) {
        perror("setsockopt() error");
        exit(1);
    } else
        printf("setsockopt() is OK.\n");

    /* host byte order */
    my_addr.sin_family = AF_INET;
    /* short, network byte order */
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    /* zero the rest of the struct */
    memset(&(my_addr.sin_zero), 0, 8);

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) == -1) {
        perror("Server-bind() error lol!");
        exit(1);
    } else
        printf("Server-bind() is OK...\n");

    /*....other codes....*/

    return 0;
}

