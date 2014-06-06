/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on June 6, 2014, 8:45 PM
 */

#include <iostream>

using namespace std;

class A{ public: virtual void foo() { cout << "A.foo\n";}};

class B{ public: void foo() { cout << "B.foo\n";}};

class C{ public: void foo() { cout << "C.foo\n";}};

class D: public A, public B, public C{
    public: void foo() { cout << "D.foo\n";}
};

/*
 * 
 */
int main(int argc, char** argv) {

    D d;
    d.A::foo();
    d.B::foo();
    d.C::foo();
    d.D::foo();
    d.foo();
    
    D* dp = new D();
    dp->A::foo();
    dp->B::foo();
    dp->C::foo();
    dp->D::foo();
    dp->foo();
    delete dp;
    
    A* ap = new D();
    ap->A::foo();
    ap->foo();
    delete ap;
    return 0;
}

