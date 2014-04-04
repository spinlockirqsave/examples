/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on August 16, 2013, 11:36 PM
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
 *  UDP server
 */

int main() {
    // datagram sockets and recvfrom()
    struct addrinfo hints, *res;
    int sockfd;
    int byte_count;
    socklen_t fromlen;
    struct sockaddr_storage addr;
    char buf[512];
    char ipstr[INET6_ADDRSTRLEN];

    // get host info, make socket, bind it to port 4950
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "9999", &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);

    // no need to accept(), just recvfrom():

    fromlen = sizeof addr;
    byte_count = recvfrom(sockfd, buf, sizeof buf, 0, (sockaddr*)&addr, &fromlen);

    printf("recv()'d %d bytes of data in buf \n", byte_count);
    printf("data: %s\n", buf);
    printf("from IP address %s\n",
            inet_ntop(addr.ss_family,
            (const void*)(&((struct sockaddr_in *) &addr)->sin_addr), ipstr, sizeof ipstr));

    return 0;
}



