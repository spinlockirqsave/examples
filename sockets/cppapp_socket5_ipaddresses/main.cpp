/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 28, 2013, 5:05 PM
 */

#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

struct tf{
    int i;
    bool tf;
};

class foo{
public:
    tf t;
    int u;
};

int main() {
    struct ifaddrs * ifAddrStruct = NULL, * ifa = NULL;
    void * tmpAddrPtr = NULL;

    //struct in_addr* mask;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        foo f;
        void* f_ptr = &f;
        void* ft_ptr = &f.t;
        void* fti_ptr = &f.t.i;
        void* fttf_ptr = &f.t.tf;
        f.t.tf=true;
        if (ifa ->ifa_addr->sa_family == AF_INET) { // check it is IP4
            char mask[INET_ADDRSTRLEN];
            void* m_ptr = (void*)&mask;
            m_ptr=m_ptr;f_ptr=f_ptr;ft_ptr=ft_ptr;fti_ptr=fti_ptr;fttf_ptr=fttf_ptr;
            void* mask_ptr = &((struct sockaddr_in*) ifa->ifa_netmask)->sin_addr;
            inet_ntop(AF_INET, mask_ptr, mask, INET_ADDRSTRLEN);
            
            f.t.i=100;
            f.t.tf=false;
            if (strcmp(mask, "255.0.0.0") != 0) {
                printf("mask:%s\n", mask);

                // is a valid IP4 Address
                tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

                printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
                // is a valid IP6 Address
                tmpAddrPtr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            }
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
    return 0;
}

