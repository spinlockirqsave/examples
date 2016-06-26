/* 
 * File:   main.cpp
 * Author: peter 
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
    
    /**
     * cin.getline behaves like get except that
     * it removes terminator from the istream 
     */
    while ( std::cin.getline( word[i], MAX, '\n') && i < 100)
    {
        /* cin.getline always appends '0' as last character
         * if number of chars (not taking into account the
         * terminator)  written to istream is:
         * >= MAX : fill appropriate word[10][i]
         * (with '0' added at the end) and return false
         * < MAX  : fill appropriate word[10][i]
         * (with '0' added at the end) and return true
         */
        std::cout << word[i++];
    }
    return 0;
}

