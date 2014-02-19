/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 19, 2014, 1:24 AM
 */

#include <cstdlib>

using namespace std;

struct A {
    int i_;
    //A( int i) : i_(i) {}
    void f() {
        *this = A({2});
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    A a({7});
    a.f();
    return 0;
}

