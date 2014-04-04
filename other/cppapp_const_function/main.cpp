/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on September 15, 2013, 2:41 AM
 */

#include <cstdlib>

using namespace std;

class B {
    int i;
public:
    int j;
    int* i_ptr;
};

class A {
    int i;
    int* i_ptr;
    B* b;
    
public:
    void f() const {
        //i = 3; error: assignment of data-member ‘A::i’ in read-only structure
        //i_ptr = new int(3); error: assignment of data-member ‘A::i_ptr’ in read-only structure
        //b.j = 0; error: assignment of data-member ‘B::j’ in read-only structure
        b->i_ptr = new int(3);  // OK
    }
    
    A() : b(new B) {}
};


/*
 * 
 */
int main(int argc, char** argv) {

    A a;
    a.f();
    return 0;
}

