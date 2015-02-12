/* 
 * File:   main.cpp
 * Author: peter peter cf16.eu
 *
 * Created on November 3, 2013, 3:50 AM
 */

#include <stdio.h>
#include <vector>
using namespace std;

class A {
public:
    //A(int i) : i_(i), v_(10) {}
    //A(int i, int j) : i_(i), j_(j) {}
    vector< int*> v_;
    int i_;
    int j_;
};

int main() {
    //A a(9); // v size is 10
    //A b(1, 2); // v size is 0
    
    A a1;
    A a2 = A();
    return 0;
}

