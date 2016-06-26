/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on February 5, 2014, 9:42 PM
 */

#include <iostream>

/*
 * 
 */
int main(int argc, char** argv) {

    char buf[10];
    char c;
    while ( std::cin)
    {
        std::cin.get( buf, 10); // newline is terminator
        /* get() always leaves terminator in the stream
         * so it becomes first character in the stream on next read */
        std::cout << buf;
        /* oops, forgot to remove '\n' from the cin...
         * never call get twice without removing the terminator */
    }
    return 0;
}

