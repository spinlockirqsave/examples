/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 27, 2014, 11:00 AM
 */

#include <stdio.h>

using namespace std;

/*
 * 
 */
#include <iostream>

char ch[] = "abcd";

int main() {

    std::cout << (long) (int*) (ch + 0) << ' '
            << (long) (int*) (ch + 1) << ' '
            << (long) (int*) (ch + 2) << ' '
            << (long) (int*) (ch + 3) << std::endl;

    std::cout << *(int*) (ch + 0) << ' '
            << *(int*) (ch + 1) << ' '
            << *(int*) (ch + 2) << ' '
            << *(int*) (ch + 3) << std::endl;
    
    char* p = ch;
    char* cp = (char*)(ch + 3);
    int* ip = (int*)(ch + 3);

    //printf( "%d, %d, %d", p, cp, ip);

    std::cout << int('abcd') << ' '
            << int('bcd') << ' '
            << int('cd') << ' '
            << int('d') << std::endl;
}

