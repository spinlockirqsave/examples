/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on July 21, 2013, 12:28 PM
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

 
/* the port users will be connecting to */
#define MYPORT 3440
/* how many pending connections queue will hold */
#define BACKLOG 10

int main() {
    /* listen on sock_fd, new connection on new_fd */
    int sockfd, new_fd;
    /* my address information, address where I run this program */
    struct sockaddr_in my_addr;
    /* remote address information */
    struct sockaddr_in their_addr;
    int sin_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket() error lol!");
        exit(1);
    } else
        printf("socket() is OK...\n");

    /* host byte order */
    my_addr.sin_family = AF_INET;
    /* short, network byte order */
    my_addr.sin_port = htons(MYPORT);
    /* auto-fill with my IP */
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* zero the rest of the struct */
    memset(&(my_addr.sin_zero), 0, 8);

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) == -1) {
        perror("bind() error lol!");
        exit(1);
    } else
        printf("bind() is OK...\n");

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen() error lol!");
        exit(1);
    } else
        printf("listen() is OK... LISTENING on interface: %s, port: %d\n",inet_ntoa(my_addr.sin_addr),MYPORT);

    /* ...other codes to read the received data... */
    printf("listening...\n");
    sin_size = sizeof (struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *) &their_addr, (socklen_t*)&sin_size);

    if (new_fd == -1)
        perror("accept() error lol!");
    else
        printf("accept() is OK...\n");

    /*.....other codes.......*/

    close(new_fd);
    close(sockfd);
    
    return 0;
}

