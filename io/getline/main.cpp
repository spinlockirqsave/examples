/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 6, 2014, 9:39 AM
 */

#include <iostream>

/*
 * 
 */
#define MAX 10
int main(int argc, char** argv) {

    char word[100][MAX];
    int i = 0;
    while ( std::cin.getline( word[i], MAX, '\n') && i < 100)
    {
        /* con.getline always appends '0' as last character
         * if number of chars (not taking into account the
         * terminator)  written to cin is:
         * >= MAX : fill appropriate word[10][i]
         * (with '0' added at the end) and return false
         * < MAX  : fill appropriate word[10][i]
         * (with '0' added at the end) and return true
         */
        std::cout << word[i++];
    }
    return 0;
}

