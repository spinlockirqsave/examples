/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on September 8, 2013, 1:08 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */
int undefined_behavior(){
   int m = 4;
   //printf("m++ + ++m: %d", m++ + ++m);
   return m;
}

class A{
    int u;
};

int j;

int main(int argc, char** argv) {

    int i;
    A a;
    A* a_ptr1 = new A;
    A* a_ptr2 = new A();
    
    int k=0;
    //k = i++ + ++i;
    
    printf("sizeof(unsigned int): %d\n",sizeof(unsigned int));
    int n = 300;
//    while(n){
//        printf("n: %d, ret: %d\n", n, n);//undefined_behavior());
//        n--;
//    }
    for(int i=300;i>1;i--){
        printf("n: %d, ret: %d\n", n, n);
        //n--;
    }
    
    return 0;
}