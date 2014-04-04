/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on August 16, 2013, 11:58 PM
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

/*
 *   UDP client
 */

#define DEST_PORT 9999
#define DEST_IP "127.0.0.1"

int main(int argc, char** argv) {
    char *secret_message = "The Cheese is in The Toaster";

    int stream_socket, dgram_socket;
    struct sockaddr_in dest_addr;
    int temp;

    // first with TCP stream sockets:

//    // assume sockets are made and connected
//    //stream_socket = socket(...
//    //connect(stream_socket, ...
//
//    // convert to network byte order
//    temp = htonl(spatula_count);
//    // send data normally:
//    send(stream_socket, &temp, sizeof temp, 0);
//
//    // send secret message out of band:
//    send(stream_socket, secret_message, strlen(secret_message) + 1, MSG_OOB);

    // now with UDP datagram sockets:
    // datagram sockets and recvfrom()
    dest_addr.sin_family = AF_INET;
    /* short, network byte order */
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
 
    /* zero the rest of the struct */
    memset(&(dest_addr.sin_zero), 0, 8);

    dgram_socket = socket(dest_addr.sin_family, SOCK_DGRAM, 0);


    // send secret message normally:
    sendto(dgram_socket, secret_message, strlen(secret_message) + 1, 0,
            (struct sockaddr*) &dest_addr, sizeof dest_addr);

    return 0;
}

