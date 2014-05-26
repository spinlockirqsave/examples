/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 26, 2014, 12:17 PM
 */

#include <iostream>
#include <stdio.h>

class A {
public:
    virtual void f() { printf( " A::f");}
    void g() { printf( " A::g");}
    static void h() { printf( " A::h");}
};

class B : public A {
public:
    virtual void f() { printf( " B::f");}
    void g() { printf( " B::g");}
    static void h() { printf( " B::h");}
};
/*
 * 
 */
int main(int argc, char** argv) {

    A* pa;
    B* pb;
    
    pa = pb = new B();
    
    pa->f();
    pa->g();
    pa->h();
    
    pb->f();
    pb->g();
    pb->h();
    
    return 0;
}

