/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 31, 2014, 05:01 PM
 * 
 * 
 */

#include <algorithm>
#include <vector>
#include <unistd.h>

class A {
public:
    A() {
        int i = 100;
    }
    A( int i) {
        int j = i;
    }
};

int main( int argc, char** argv) {
    //sleep( 15);
    std::vector<int> v;
    std::uninitialized_fill( v.begin(), v.end(), 9);
    
    std::vector<A> av(10);
    std::uninitialized_fill( av.begin(), av.end(), A());
    
    return 0;
}