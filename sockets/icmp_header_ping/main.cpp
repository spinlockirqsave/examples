/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 * http://stackoverflow.com/questions/22149452/creating-ethernet-frame-in-sock-raw-commmunication#22149452
 *
 * Created on March 3, 2014, 4:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define DEFAULT_NUM_PACKETS 10

char buf[BUFFER_SIZE]; 
const char *message = "\n ./output_file <sender_ip_addr> <dest_ip_addr> <no_of_reqs>\n \
        <no_of_req> = is the number of requests to send and 10 is the default and mentioning 0  is infinite\n";

void set_ip_layer_fields(struct icmphdr *icmp, struct ip *ip)
{
    // IP layer
    ip->ip_v = 4;
    ip->ip_hl = sizeof*ip >> 2;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(buf));
    ip->ip_id = 0;
    ip->ip_off = 0;
    ip->ip_ttl = 255;
    ip->ip_p = 1;
    ip->ip_sum = 0; 

    // ICMP Layer
    icmp->type = 8;
    icmp->code = 0;     
    icmp->checksum = htons(~(ICMP_ECHO << 8));  
}

int main(int argc, char *argv[])
{
    int s, i ;  
    struct ip *ip = (struct ip *)buf;
    struct icmphdr *icmp = (struct icmphdr *)(ip + 1);
    struct hostent *hp, *hp2;
    struct sockaddr_in dst;                               
    int num = DEFAULT_NUM_PACKETS;

    if(argc < 3)
    {
        fprintf(stdout, "%s\n",message);
        exit(1);
    }

    // If enough arguments supplied 
    if(argc == 4)
        num = atoi(argv[3]);

    // Loop based on the no of requests
    for(i = 1; num == 0 ? num == 0 : i <= num; i++)
    {
        memset(buf, 0, sizeof(buf));

        if((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
        {
            perror("socket() error");
            exit(1);
        }

        if((hp = gethostbyname(argv[2])) == NULL)
        {
            if((ip->ip_dst.s_addr = inet_addr(argv[2])) == -1)
            {
                fprintf(stderr, "%s: unknown host.\n", argv[2]);
                exit(1);
            }
        }

        else
            memcpy(&ip->ip_dst.s_addr, hp->h_addr_list[0], hp->h_length);

        if((hp2 = gethostbyname(argv[1])) == NULL)
        {
            if((ip->ip_src.s_addr = inet_addr(argv[1])) == -1)
            {
                fprintf(stderr, "%s: unknown host\n", argv[1]);
                exit(1);
            }
        }
        else
            memcpy(&ip->ip_src.s_addr, hp2->h_addr_list[0], hp->h_length);

        set_ip_layer_fields(icmp, ip);

        dst.sin_addr = ip->ip_dst;
        dst.sin_family = AF_INET;

        if(sendto(s, buf, sizeof(buf), 0, (struct sockaddr *)&dst, sizeof(dst)) < 0)
        {
            fprintf(stderr, "error while sending\n");
        }
        else
            printf("request:%d sended successfully\n",i);

        close(s);

    }
    return 0;
}

