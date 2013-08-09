/* 
 * File:   main.cpp
 * Author: Piotr Gregor  postmaster@cf16.eu
 *
 * Created on August 3, 2013, 10:01 PM
 */

#include <sys/socket.h>
#include <netinet/in.h>

//#include <unistd.h>
//#include <sys/types.h>
//#include <arpa/inet.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

/*
 * 
 */
#include <iostream>
#include <string>

void passAsVoid(const void* v) {
    std::cout << (const char*)v << std::endl;
}

int main(int argc, char** argv) {

    // Later in the code

sockaddr_in serverAddress;
memset(&serverAddress, '0', sizeof(serverAddress));
serverAddress.sin_family = INADDR_ANY;
serverAddress.sin_port = htons(192.168);
serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

const char* x = "x";
std::cout << x << std::endl;

passAsVoid(x);

std::string s("piotrus");

    return 0;
}

