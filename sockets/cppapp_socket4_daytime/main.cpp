/* 
 * File:   main.cpp
 * Author: piter  cf16.eu
 *
 * Created on July 24, 2013, 1:21 AM
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "error_functions.h" //from http://man7.org/tlpi/code/online/dist/lib/error_functions.c.html

#include <time.h>
/*
 * 
 */

int connectsock(const char *host, const char *service, const char *transport)
{
    struct hostent      *phe;   /* pointer to host information entry    */
    struct servent      *pse;   /* pointer to service information entry */
    struct protoent     *ppe;   /* pointer to protocol information entry*/
    struct sockaddr_in sin;     /* an Internet endpoint address         */
    int s, type;                /* socket descriptor and socket type    */
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    /* Map service name to port number */
    if(pse = getservbyname(service, transport))
        sin.sin_port = pse->s_port;
    else if ((sin.sin_port = htons((u_short)atoi(service))) == 0)
        errExit("can't get \"%s\" service entry\n", service);
    /* Map host name to IP address, allowing for dotted decimal */
    if(phe = gethostbyname(host))
        memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
    else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
        errExit("can't get \"%s\" host entry\n", host);
    /* Map transport protocol name to protocol number */
    if((ppe = getprotobyname(transport)) == 0)
        errExit("can't get \"%s\" protocol entry\n", transport);
    /* Use protocol to choose a socket type */
    if(strcmp(transport, "udp") == 0)
        type = SOCK_DGRAM;
    else
        type = SOCK_STREAM;
    /* Allocate a socket */
    s = socket(PF_INET, type, ppe->p_proto);
    if(s < 0)
       errExit("can't create socket: %s\n", strerror(errno));
    /* Connect the socket */
    if(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
       errExit("can't connect to %s.%s: %s\n", host, service, strerror(errno));
    return s;
}

u_short portbase = 0;

int passivesock(const char *service, const char *transport, int qlen)
{
    struct servent  *pse;
    struct protoent *ppe;
    struct sockaddr_in sin;
    int     s, type;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    /* Map service name to port number */
    if(pse = getservbyname(service, transport))
        sin.sin_port = htons(ntohs((u_short)pse->s_port) + portbase);
    else if((sin.sin_port = htons((u_short)atoi(service))) == 0)
        errExit("can't get \"%s\" service entry\n", service);
    /* Map protocol name to protocol number */
    if((ppe = getprotobyname(transport)) == 0)
        errExit("can't get \"%s\" protocol entry\n", transport);
    /* Use protocol to choose a socket type */
    if(strcmp(transport, "udp") == 0)
        type = SOCK_DGRAM;
    else
        type = SOCK_STREAM;
    /* Allocate a socket */
    s = socket(PF_INET, type, ppe->p_proto);
    if(s < 0)
        errExit("can't create socket: %s\n", strerror(errno));
    /* Bind the socket */
    if(bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
        errExit("can't bind to %s port: %s\n", service, strerror(errno));
    if(type == SOCK_STREAM && listen(s, qlen) < 0)
        errExit("can't listen on %s port: %s\n", service, strerror(errno));
    return s;
}

int passiveTCP(const char *service, int qlen){
    return passivesock(service, "tcp", qlen);
}

void TCPdaytimed(int fd){
    char *pts;
    time_t now;
    //char *ctime();
    time(&now);
    pts = ctime(&now);
    write(fd, pts, strlen(pts));
    char mes[35] = "\rUnix timestamp: ";
    char buffer[15];
    snprintf(buffer, sizeof(buffer), "%d\r\n", now);
    strcat(mes,buffer);
    write(fd, mes, strlen(mes));
    return;
}

int main(int argc, char** argv) {
    
    FILE* fp, *ferr;
    ferr = freopen("/home/piter/log/log_cppapp_socket4_daytime.txt", "a", stderr);
    
    struct sockaddr_in theirAddr;
    char *service = "daytime";
    int msock, ssock;
    int alen;
    msock = passiveTCP(service, 5);
    while (1) {
        ssock = accept(msock, (struct sockaddr *)&theirAddr, (socklen_t*)&alen);
        if(ssock < 0)
            errExit("accept failed: %s\n", strerror(errno));
        char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, (void*)&theirAddr.sin_addr, addressBuffer, INET_ADDRSTRLEN);
        //char* m = "Hello, cf16 DAYTIME service here.\nThe time on this server is now: ";
        //const int size = strlen(m)+INET_ADDRSTRLEN+2;
                char message[100] = "Hello, ";
                strcat(message, addressBuffer);
                char* m = ". cf16 DAYTIME service here.\r\nThe time on this server is now: ";
                strcat(message, m);
        write(ssock,message,strlen(message));
        TCPdaytimed(ssock);
        char* mes = "\nCan I still assist you? [yes/no]: ";
        write(ssock,mes,strlen(mes));
#define MAXDATASIZE 200
        int left = MAXDATASIZE;
        char buf[MAXDATASIZE], *b;
        int bytes = 0, totalBytes = 0;
        b=buf;
//        while((bytes = read(ssock,buf,MAXDATASIZE-1) > 0) && left){ // read in chunks, reads only 1 byte. TODO: why ?????
//            totalBytes+=bytes;
//            b+=bytes;
//            left-=bytes;
//        }
        totalBytes = read(ssock,buf,MAXDATASIZE-1); // read all at once, works
        if (totalBytes > 2) {
            if ((fp = freopen("/home/piter/log/log_cppapp_socket4_daytime.txt", "a", stdout)) == NULL) {
                printf("ERROR cppapp_socket4_daytime: Cannot write to file /home/piter/log/log_cppapp_socket4_daytime.txt.\n");
                exit(1);
            }
            char *pts;
            char ptsres[25];
            ptsres[24]='\0';
            time_t now;
            time(&now);
            pts = ctime(&now);
            strncpy(ptsres,pts,24);
            char buf2[totalBytes-1];
            buf2[totalBytes-2]='\0';
            strncpy(buf2,buf,totalBytes-2);
            printf("%s, Client with IP %s says: %s\n", ptsres, addressBuffer, buf2);
            fclose(fp);
        }
        
        char* mes2="\r\nSorry, this is not implemented yet.\r\nClosing connection.\r\n";
        write(ssock,mes2,strlen(mes2));
        //char debug[5]="abc\n";
        //write(ssock,debug,strlen(debug));
        //write(ssock,debug,strlen(debug));
        //write(ssock,debug,strlen(debug));
        close(ssock);
  }
    fclose(ferr);
    return 0;
}

