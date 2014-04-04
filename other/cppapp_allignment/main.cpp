/* 
 * File:   main.cpp
 * Author: Piotr Gregor  piter@cf16.eu
 *
 * Created on July 13, 2013, 4:17 PM
 */
#include "usr/include/c++/4.4/bits/basic_string.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <boost/timer.hpp>
#include <sys/time.h>
#include <memory.h>
#include <bitset>
using namespace std;

class Timer {
private:

    timeval startTime;

public:

    void start(){
        gettimeofday(&startTime, NULL);
    }

    double stop(){
        timeval endTime;
        long seconds, useconds;
        double duration;

        gettimeofday(&endTime, NULL);

        seconds  = endTime.tv_sec  - startTime.tv_sec;
        useconds = endTime.tv_usec - startTime.tv_usec;

        duration = seconds + useconds/1000000.0;

        return duration;
    }
    
    long stop_useconds(){
        timeval endTime;
        long useconds;

        gettimeofday(&endTime, NULL);
        useconds = endTime.tv_usec - startTime.tv_usec;

        return useconds;
    }

    static void printTime(double duration){
        printf("%5.6f seconds\n", duration);
    }
};

/*
 * 
 */
void Munge8( void *data, uint32_t size ) {
    uint8_t *data8 = (uint8_t*) data; //0x7fffffffe3d0
    uint8_t *data8End = data8 + size; //0x7fffffffe3da
    
    while( data8 != data8End ) { //number of accesses: size = 10
        *data8++ = -*data8;
    }
}

void Munge16( void *data, uint32_t size ) {
    uint16_t *data16 = (uint16_t*) data;
    uint16_t *data16End = data16 + (size >> 1); // Divide size by 2. = data16+5(uint16_t)=data16+10bytes
    //data16End will be same address as data8End address (here=data+10bytes=0x7fffffffe3d0+10=0x7fffffffe3da)
    //tab itself is 10*4 bytes long (10 ints), but size=10 in function Munge8 is treated as uint8_t(10bytes)
    uint8_t *data8 = (uint8_t*) data16End;
    uint8_t *data8End = data8 + (size & 0x00000001); /* Strip upper 31 bits. */
    
    while( data16 != data16End ) { //number of accesses: size>>1, here 10/2=5
        *data16++ = -*data16;
    }
    while( data8 != data8End ) { //0 accesses
        *data8++ = -*data8;
    }
}

void Munge32( void *data, uint32_t size ) {
    uint32_t *data32 = (uint32_t*) data;
    uint32_t *data32End = data32 + (size >> 2); /* Divide size by 4. */
    uint8_t *data8 = (uint8_t*) data32End;
    uint8_t *data8End = data8 + (size & 0x00000003); /* Strip upper 30 bits. */
    
    while( data32 != data32End ) { //number of accesses: size>>2, 10/4=2.5 =>2
        *data32++ = -*data32;
    }
    while( data8 != data8End ) { //2 accesses
        *data8++ = -*data8;
    }
}


void Munge64( void *data, uint32_t size ) {
    double *data64 = (double*) data;
    double *data64End = data64 + (size >> 3); /* Divide size by 8. */
    uint8_t *data8 = (uint8_t*) data64End;
    uint8_t *data8End = data8 + (size & 0x00000007); /* Strip upper 29 bits. */
    
    while( data64 != data64End ) {
        *data64++ = 1;//-*data64;
    }
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
}

void Munge8debug( void *data, uint32_t size ) {
    uint8_t *data8 = (uint8_t*) data;
    uint8_t *data8End = data8 + size;
    printf("\ndata8 address:%p\n",data8);
    printf("data8End address:%p\n",data8End);
    
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
}

void Munge16debug( void *data, uint32_t size ) {
    uint16_t *data16 = (uint16_t*) data;
    printf("\nsize:%d\n",size);
    printf("size>>1:%d\n",size>>1);
    uint16_t *data16End = data16 +(size>>1); /* Divide size by 2. */
    uint8_t *data8 = (uint8_t*) data16End;
    uint8_t *data8End = data8 + (size & 0x00000001); /* Strip upper 31 bits. */
    printf("data8 address:%p\n",data8);
    printf("data8End address:%p\n",data8End);
    printf("data16 address:%p\n",data16);
    printf("data16End address:%p\n",data16End);
    
    while( data16 != data16End ) {
        *data16++ = -*data16;
    }
    while( data8 != data8End ) { //number of accesses: size>>2, 10/2=5 (might be less then size/2 if size%2>0)
        *data8++ = -*data8;
    }
}

void Munge32debug( void *data, uint32_t size ) {
    uint32_t *data32 = (uint32_t*) data;
    uint32_t *data32End = data32 + (size >> 2); // Divide size by 4. 10>>2=2 dataEnd=data32+2*4=data32+8=0x7fffffffe3d8
    uint8_t *data8 = (uint8_t*) data32End;
    uint8_t *data8End = data8 + (size & 0x00000003); /* Strip upper 30 bits. */
    
    while( data32 != data32End ) { //number of accesses: size>>2 (might be less then size/4 if size%4>0 as here it is)
        *data32++ = -*data32;
    }
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
}

#define TPS CLOCKS_PER_SEC

int main(int argc, char** argv) {
    
    printf("sizeof(uint8_t):%ld\n",sizeof(uint8_t));
    printf("sizeof(uint16_t):%ld\n",sizeof(uint16_t));
    printf("sizeof(uint32_t):%ld\n",sizeof(uint32_t));
    //int* tab=(int*)malloc(sizeof(uint8_t)*10);
    int tab[10]={0,1,2,3,4,5,6,7,8,9};
    printf("tab address:%p\n",tab);
    printf("tab end address:%p\n",tab+10);
    copy(tab,tab+10,ostream_iterator<int>(cout,","));
    
    //Munge32debug(tab,10);
    
    copy(tab,tab+10,ostream_iterator<uint8_t>(cout,","));
    printf("\n\n\n");
    
    //test

//    for (int i = 0; i < 10; i++) {
//         void *vp = malloc(1024*sizeof(int));
//         memset((int *)vp, 0, 1024);
//        void* itab = malloc(sizeof(int)*1024*256); //1MiB table  
//        if (itab) {
//            memset ( (int*)itab, 0, 1024*256*sizeof (int) );
//            float elapsed;
//
//            boost::timer t;
//            Timer timer = Timer();
//            timer.start();
//            t.restart();
//            Munge64(itab, 1024*256);
//
//            double duration = timer.stop();
//            long lt = timer.stop_useconds();
//            timer.printTime(duration);
//            cout << t.elapsed() << endl;
//            elapsed = t.elapsed();
//            cout << ios::fixed << setprecision(10) << elapsed << endl;
//            cout << ios::fixed << setprecision(10) << t.elapsed() << endl;
//            printf("Munge8 elapsed:%ld useconds\n", lt);
//
//            elapsed = 0;
//            free(vp);
//            free(itab);
//            //printf("Munge8 elapsed:%d\n", elapsed);
//        }
    //}
    
    int i=13;
    bitset<8> bit (i);
    cout<<bitset<8>(0xd).to_string()<<endl;
    cout<<bit.to_string();
    string s();
    return 0;
}

