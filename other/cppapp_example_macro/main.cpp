/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 22, 2013, 11:10 PM
 */

#include <stdlib.h>
#include <stdio.h>

/*
 * 
 */
#define macro1(x) (x)==1?printf("==1\n"):printf("!=1\n");

int main(int argc, char** argv) {
    int i=1,j=2;
    macro1(i)
    macro1(j)
    return 0;
}

