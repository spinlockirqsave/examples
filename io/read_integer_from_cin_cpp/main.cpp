/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on June 21, 2014, 10:57 PM
 * 
 * Custom fast input function
 * http://stackoverflow.com/questions/24345663/different-results-for-long-long-int-in-c-and-c?noredirect=1#24345758
 */

#include <stdio.h>
#include <iostream>



/*
 * Custom fast input function
 */
int read_int()
{
    char c = getchar();
    while(c<'0' || c>'9')
    c = getchar();
    int ret = 0;
    while(c>='0' && c<='9')
    {
        ret = 10 * ret + c - 48;
        c = getchar();
    }
    return ret;
}

/*
 * 
 */
int main(int argc, char** argv) {

    /* Disable sync with iostreams to get some speed */
    std::ios::sync_with_stdio(false);
    
    int x;
    std::cin >> x;
    std::cout << x + 1003;
    
    return 0;
}

