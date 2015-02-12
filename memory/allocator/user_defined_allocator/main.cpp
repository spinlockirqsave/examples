/* 
 * File:   main.cpp
 * Author: peter cf16.eu
 *
 * Created on January 26, 2014, 3:32 AM
 */

#include <memory>
#include <vector>
#include <iostream>

#include "Pool_alloc.h"
#include "Pool_alloc.cpp"

/*
 * 
 */
int main(int argc, char** argv) {   
    
    std::vector<int> v1;
    std::vector<int, Pool_alloc<int> > v2;
    
    for ( int i = 0; i < 0xc00; ++i) {
        v1.push_back( i);
        if ( !(i%20))
        std::cout << "size:" << v1.size() << ", capacity:" << v1.capacity();
    }
    
    for ( int i = 0; i < 0x100; ++i) {
        v2.push_back( i);
        if ( !(i%20))
        std::cout << "size:" << v2.size() << ", capacity:" << v2.capacity() << std::endl;
    }
    std::cout.flush();
    return 0;
}

